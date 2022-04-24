clear all
clc


lists  = dir(cd);       % 파일을 전처리가 있으면 사용

jhlen = length(lists);
AA=zeros(4,100);
BB=zeros(4,100);
CC =zeros(8,4);
fH = xlsread("sumAP.xlsx");
%
% syn=xlsread('actProfile.xlsx');
% synn=xlsread('weight.xlsx');
Rr=zeros(8,100);


iterA = 0;  iterB = 0;  iterC = 0;  iterD = 0;


for i=2:18
    
    datax=xlsread(sprintf('%d.xlsx',i));
    [datax1,datax2] = size(datax);
    data = zeros(datax1,8);
    for datanum = 1:8
        data(:,datanum) = datax(:,2*datanum-1);
    end
    
    [m,n]=size(data); % 행렬 크기
    mm=m/100;
    x=1:m;
    xx=1:mm:m;
    
    data4=data';
    
    %% cubicspline interpolation
    for p=1:n
        
        exp_tmp=['y',num2str(p),'= data4(',num2str(p),',:);'];
        eval(exp_tmp);
        
        
        exp_tmp1=['yy',num2str(p),'=spline(x,y',num2str(p),',xx);'];
        eval(exp_tmp1);
        
        exp_tmp=['yyy(p,:)=yy',num2str(p),';'];
        eval(exp_tmp)
        
        
    end
    
    yy=yyy(:,[1:100]);
    
    %% 1번바꾸기 : 101개로 2~101 이 아닌 106개로 7~101까지
    %% 정규화(normalization)
    
    
    z=yy';
    maxz=max(z);
    maxz2 = max(maxz);
    minz=min(z);
    
    interval = maxz - minz;
    
    norEMG_1 = z-minz;
    norEMG_2 = norEMG_1./interval;
    
    
    exp_tmp = [ 'Rightraw',num2str(i),'=transpose(norEMG_2);'];
    eval(exp_tmp)
    
    tmpc = 0;
    
    for jj=1:15   
        for j = -10 : 10
            for k =1:8
                exp_tmp = [ 'Rr',num2str(i),'(k,:)= circshift(Rightraw',num2str(i),'(k,:),j);'];
                eval(exp_tmp);
            end
            
            
            exp_tmp = [ ' Original_EMG = Rr',num2str(i),';'];
            eval(exp_tmp)
            
            
            opt=statset('MaxIter',10,'Display','off');
            [W0,H0]=nnmf(Original_EMG,4,'replicates',100,'options',opt,'algorithm','mult');
            
            opt = statset('Maxiter',1000,'Display','off');
            [num4W,num4H,num4D] = nnmf(Original_EMG,4,'w0',W0,'h0',H0,'replicates',1000,'options',opt,'algorithm','als');
            
            A = jh_corr2(fH,num4H);
            
            
            
            c = sum(jh_corr3(fH,num4H));        % jh_corr3 = JH_synergy distance
            
            a1= A(1,2);     b1 = A(a1+5,2);     d1 = A(1,1);
            a2= A(2,2);     b2 = A(a2+10,2);    d2 = A(2,1);
            a3= A(3,2);     b3 = A(a3+15,2);    d3 = A(3,1);
            a4= A(4,2);     b4 = A(a4+20,2);    d4 = A(4,1);
            
            
            if(tmpc < c)
                AA2 = num4H;
                BB2 = num4W;
                tmpc = c;
                shiftiter = j;
            end
        end
        
        
        
        exp_tmp = ['num4H',num2str(i),'=AA2;'];
        eval(exp_tmp);
        exp_tmp = ['num4W',num2str(i),'=BB2;'];
        eval(exp_tmp);
        exp_tmp = ['shiftiter',num2str(i),'=shiftiter;'];
        eval(exp_tmp);
        
    end


    %% 초기화
    
    
    num2DD=0;num3DD=0;num4DD=0;num5DD=0;
    num2WW=0;num3WW=0;num4WW=0;num5WW=0;
    num2HH=0;num3HH=0;num4HH=0;num5HH=0;
    
    Rightnum2DD=0;Rightnum3DD=0;Rightnum4DD=0;Rightnum5DD=0;
    Rightnum2WW=0;Rightnum3WW=0;Rightnum4WW=0;Rightnum5WW=0;
    Rightnum2HH=0;Rightnum3HH=0;Rightnum4HH=0;Rightnum5HH=0;
    
    Leftnum2DD=0;Leftnum3DD=0;Leftnum4DD=0;Leftnum5DD=0;
    Leftnum2WW=0;Leftnum3WW=0;Leftnum4WW=0;Leftnum5WW=0;
    Leftnum2HH=0;Leftnum3HH=0;Leftnum4HH=0;Leftnum5HH=0;
    

 
    
    %% 나누기
    exp_tmp = ['A= jh_corr2(fH,num4H',num2str(i),');'];
    eval(exp_tmp);
    
    a1= A(1,2);     b1 = A(a1+5,2);     d1 = A(1,1);
    a2= A(2,2);     b2 = A(a2+10,2);    d2 = A(2,1);
    a3= A(3,2);     b3 = A(a3+15,2);    d3 = A(3,1);
    a4= A(4,2);     b4 = A(a4+20,2);    d4 = A(4,1);
    
    c1 = abs(100-b1);    c2 = abs(100-b2); c3 = abs(100-b3); c4 = abs(100-b4);
    
    
    
    if((c1<6)&&(d1>0.8))
        exp_tmp = ['AA(1,:) = AA(1,:) + num4H',num2str(i),'(a1,:);'];
        eval(exp_tmp);
        exp_tmp = ['CC(:,1) = CC(:,1) + num4W',num2str(i),'(:,a1);'];
        eval(exp_tmp);
        iterA = iterA+1;
        jhiternum(1,iterA)=i;
    end
    

    
    if((c2<6)&&(d2>0.8))
        exp_tmp = ['AA(2,:) = AA(2,:) + num4H',num2str(i),'(a2,:);'];
        eval(exp_tmp);
        exp_tmp = ['CC(:,2) = CC(:,2) + num4W',num2str(i),'(:,a2);'];
        eval(exp_tmp);
        iterB = iterB+1;
        jhiternum(2,iterB)=i;
    end

    
    if((c3<6)&&(d3>0.8))
        exp_tmp = ['AA(3,:) = AA(3,:) + num4H',num2str(i),'(a3,:);'];
        eval(exp_tmp);
        exp_tmp = ['CC(:,3) = CC(:,3) + num4W',num2str(i),'(:,a3);'];
        eval(exp_tmp);
        iterC = iterC+1;
        jhiternum(3,iterC)=i;
    end

    
    if((c4<6)&&(d4>0.8))
        exp_tmp = ['AA(4,:) = AA(4,:) + num4H',num2str(i),'(a4,:);'];
        eval(exp_tmp);
        exp_tmp = ['CC(:,4) = CC(:,4) + num4W',num2str(i),'(:,a4);'];
        eval(exp_tmp);
        iterD = iterD+1;
        jhiternum(4,iterD)=i;
    end

end

AA(1,:)= AA(1,:)./iterA;
AA(2,:)= AA(2,:)./iterB;
AA(3,:)= AA(3,:)./iterC;
AA(4,:)= AA(4,:)./iterD;

CC(:,1)= CC(:,1)./iterA;
CC(:,2)= CC(:,2)./iterB;
CC(:,3)= CC(:,3)./iterC;
CC(:,4)= CC(:,4)./iterD;


AAAA(1,:) = AA(1,:)./max(AA(1,:));
AAAA(2,:) = AA(2,:)./max(AA(2,:));
AAAA(3,:) = AA(3,:)./max(AA(3,:));
AAAA(4,:) = AA(4,:)./max(AA(4,:));

CCCC(:,1) = CC(:,1)./max(AA(1,:));
CCCC(:,2) = CC(:,2)./max(AA(2,:));
CCCC(:,3) = CC(:,3)./max(AA(3,:));
CCCC(:,4) = CC(:,4)./max(AA(4,:));




xlswrite("AA.xlsx",AA);
xlswrite("CC.xlsx",BB);


        
