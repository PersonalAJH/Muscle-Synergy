function [ fixW, H ] = Wfix( EMGenvelop,fixW, itr, K )

    tic;
    
    exe_time = 0;
    
    wrt = zeros( itr , 2 );
    
    [numberEMG,numberSample] = size( EMGenvelop );
    
    H = abs(randn( K, numberSample ));
     
    Xf = fixW * H;
    
    % Iteration by MU
    for lp=1:itr
     

      % update V
     H = H .* ((fixW' * EMGenvelop) ./ (fixW' * Xf));
    
      Xf = fixW * H;
      
      
      exe_time = exe_time + toc;
      
      error = norm( EMGenvelop - Xf, 'fro' )^2;
      
      wrt(lp,:) = [ exe_time  error ];
      
      tic;
    
    end
    
    
end
