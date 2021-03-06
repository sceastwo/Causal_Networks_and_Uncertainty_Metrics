format long e;

PrR = [ 0.5 ; 0.3 ; 0.2 ];
PrV = [ 0.99 ; 0.01 ];
PrS = [ 1.00, 0.00, 0.00, 0.00, ...
        0.00, 0.00, 0.00, 1.00, ...
        0.65, 0.05, 0.05, 0.25, ... 
        0.05, 0.05, 0.15, 0.75, ...
        0.40, 0.05, 0.05, 0.50, ...
        0.40, 0.05, 0.05, 0.50 ];
PrS = reshape(PrS,[4,2,3]);
PrC = [ 1.0, 0.0, 0.0, ...
        0.8, 0.2, 0.0, ...
        0.5, 0.5, 0.0, ...
        0.0, 0.0, 1.0, ...
        0.0, 0.0, 1.0, ...
        0.0, 0.2, 0.8, ...
        0.0, 0.5, 0.5, ...
        1.0, 0.0, 0.0 ];
PrC = reshape(PrC,[3,4,2]);

Pr = zeros(3,4,2,3);
for R = 1:3 
    for V = 1:2
        for S = 1:4
            for C = 1:3
                Pr(C,S,V,R) = PrR(R)*PrV(V)*PrS(S,V,R)*PrC(C,S,V);
            end;
        end;
    end;
end;







