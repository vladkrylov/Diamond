function test_poisson
    N_bins = 200;
    
    files = {
        '../lambda=4.2.csv'...
        ,'../expdata__Run16__Beamtime5.csv'...
        };
    
    L = length(files);
    x = zeros(N_bins, L);
    y = zeros(N_bins, L);
    legendInfo = cell(1,L);
    
    for i=1:L
        data = load(files{i});
        
        if i ~= L
            [counts, centers] = hist(data(1:1e4), N_bins);
            x(:,i) = MeV2Volts(centers.');
        else
            [counts, centers] = hist(data, N_bins);
            x(:,i) = centers.' - 0.003;
        end
        y(:,i) = smooth(counts.', 10);
        
        [pathstr,name,ext] = fileparts(files{i});
        legendInfo{i} = name;
    end
    
    figure(1)
    stairs(x, y)
<<<<<<< Updated upstream
=======
    
%     x_centers = 1000;
    x_centers = 18.7 * [-0.01:1e-4:0.35];
    
    hold on
        legendInfo = sim_plot(4.2, 1e4, x_centers, 10, 'r', legendInfo);
        legendInfo = sim_plot(2.9, 1e4, x_centers, 10, 'g', legendInfo);
    hold off
>>>>>>> Stashed changes
    legend(legendInfo)
end

function y = MeV2Volts(x)
    y = x / 0.226 * 0.012;
end