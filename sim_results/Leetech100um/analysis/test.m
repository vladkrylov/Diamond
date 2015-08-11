function test
    N_bins = 1000;
    
    figure(1)
    hold on
    
%     d2 = load('../1e.csv');
%     [y2, x2] = hist(d2, N_bins);
%     stairs(x2(2:end), y2(2:end), 'r')

    dm = load('../many3.csv');
    [y2, x2] = hist(dm, N_bins);
    stairs(x2(2:end), y2(2:end), 'r')
    
    hold off
end