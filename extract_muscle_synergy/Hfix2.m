function [  W, fixH ] = Hfix( EMGenvelop,fixH, itr, K )

    tic;
    
    exe_time = 0;
    
    wrt = zeros( itr , 2 );
    
    [numberEMG,numberSample] = size( EMGenvelop );
    

    W = abs(randn( numberEMG, K ));
     
    Xf = W * fixH;
    
    % Iteration by MU
    for lp=1:itr
     
      % update T
      W = W .* ((EMGenvelop * fixH') ./ (Xf * fixH'));
    
      Xf = W * fixH;
      
      
      exe_time = exe_time + toc;
      
      error = norm( EMGenvelop - Xf, 'fro' )^2;
      
      wrt(lp,:) = [ exe_time  error ];
      
      tic;
    
    end
    
    
end
