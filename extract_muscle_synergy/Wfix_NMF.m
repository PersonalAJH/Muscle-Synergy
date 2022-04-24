
clear all
clc


AA=zeros(8,4);
BB=zeros(8,4);

% 
 fixH=xlsread('fH.xlsx');       
 fixW=xlsread('fW.xlsx');
 
 

for i=2:20

    data=xlsread(sprintf('%d.xlsx',i));

    
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
    
    interval = maxz2 - minz;

    norEMG_1 = z-minz;
    norEMG_2 = norEMG_1./interval;
    

    exp_tmp = [ 'Rightraw',num2str(i),'=transpose(norEMG_2);'];
    eval(exp_tmp)
    
    
    
        tmpc = 0;
    
    for jj=1:15
        for j = -10 : 10
            
            exp_tmp = [ 'Rr',num2str(i),'= circshift(Rightraw',num2str(i),',j);'];
            eval(exp_tmp);
            exp_tmp = [ ' Original_EMG = Rr',num2str(i),';'];
            eval(exp_tmp)
            
            
            [num4W,num4H]=Wfix2(Original_EMG,fixW,2000,4);
                     
            AA=AA+num4W;
            
            

            A = jh_corr2(fixH,num4H);
            
            c = sum(jh_corr3(fixH,num4H));        % jh_corr3 = JH_synergy distance
            
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

    
end



AA=AA./18;
BB=BB./18;

xlswrite("RnorW.xlsx",AA);
xlswrite("LnorW.xlsx",BB);


    
