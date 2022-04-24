
clear all
clc


AA=zeros(8,4);
BB=zeros(8,4);

% 
 fixH=xlsread('fH.xlsx');       
 fixW=xlsread('fW.xlsx');
 
 

for i=2:20

    data=xlsread(sprintf('%d.xlsx',i));

    
    [m,n]=size(data); % ��� ũ��
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
    
    %% 1���ٲٱ� : 101���� 2~101 �� �ƴ� 106���� 7~101����
    %% ����ȭ(normalization)
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
            
            
            [num4W,num4H]=Hfix2(Original_EMG,fixH,2000,4);
            
            exp_tmp=['num4W',num2str(i),'=num4W;'];
            eval(exp_tmp);
            exp_tmp=['num4H',num2str(i),'=num4H;'];
            eval(exp_tmp);
            

            
            c = sum(jhcos(fixW,num4W));        % jh_corr3 = JH_synergy distance
        
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


    
