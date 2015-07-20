function lambda = get_lambda(n_zeros, n_nonzeros)
    options = optimset('TolX', 1e-2);
    lambda = fsolve(@(x)f(x, n_zeros, n_nonzeros), 1, options);
    
end

function y = f(x, n_zeros, n_nonzeros)
    N0 = poisspdf(0, x) * (n_zeros + n_nonzeros);
    y = n_zeros - N0;
end