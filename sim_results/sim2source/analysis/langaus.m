function y_conv = langaus(par, x)
% par(1) = Width (scale) parameter of Landau density
% par(2) = Most Probable (MP, location) parameter of Landau density
% par(3) = Total area (integral -inf to inf, normalization constant)
% par(4) = Width (sigma) of convoluted Gaussian function
    sgm = par(1);
    xc = par(2);
    a = par(3);
    sgm_gauss = par(4);

    y = a./(x*sgm*sqrt(2*pi)).*exp(-0.5*((log(x)-xc)/sgm).^2);
    y_conv = y;

    L = length(y);
    for i=1:L
        gauss_filter = exp(-(x-x(i)).^2./(2*sgm_gauss^2));
        gc = y .* gauss_filter;
        y_conv(i) = sum(gc);
    end
    y_conv = y_conv / L;
end
