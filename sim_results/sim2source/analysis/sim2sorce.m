function sim2sorce
    clear all; clc;
    load('/run/media/vlad/00789D9D789D91D0/Leetech/Diamond++/VLAD/ampl_max24_all.mat');
    
    xbins = 0:1e-4:0.05;

    figure(1);
    [counts, centers] = hist(ampl_max, xbins);
    
    inds = centers > 0.005;
    x = centers(inds);
    y = counts(inds);
    
    x0 = [0.17, -4.4, 0.88, 0.002];
    params = lsqcurvefit(@langaus, x0, x, y);
    plot(x, y)
    hold on
        plot(x, langaus(params, x), '-r', 'LineWidth', 1)
    hold off
%     ylim([0, 1.1*max(y)])
end

