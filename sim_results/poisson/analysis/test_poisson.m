function test_poisson
    N_bins = 1000;
    
    files = {
        '../expdata__Run16__Beamtime5.csv'...
        };
%             '../lambda=4.2.csv'...
    
    L = length(files);
    x = zeros(N_bins, L);
    y = zeros(N_bins, L);
    legendInfo = cell(1,L);
    
    for i=1:L
        data = load(files{i});
        
        [counts, centers] = hist(data, N_bins);
        x(:,i) = centers.' - 0.003;
        y(:,i) = smooth(counts.', 10);
        
        [pathstr, name, ext] = fileparts(files{i});
        legendInfo{i} = name;
    end
    figure(1)
    stairs(x, y)
<<<<<<< HEAD
    
=======
<<<<<<< Updated upstream
=======
    
%     x_centers = 1000;
>>>>>>> develop
    x_centers = 18.7 * [-0.01:1e-4:0.35];
    
    hold on
        legendInfo = sim_plot(4.2, 1e4, x_centers, 10, 'r', legendInfo);
        legendInfo = sim_plot(2.9, 1e4, x_centers, 10, 'g', legendInfo);
    hold off
<<<<<<< HEAD
=======
>>>>>>> Stashed changes
>>>>>>> develop
    legend(legendInfo)
    xlabel('Amplitude, V')
    ylabel('Counts')
end

function legendInfo = sim_plot(lambda, n_events, n_bins, n_smooth, color, legend)
    [x_sim, y_sim] = g4poisson(lambda, n_events, n_bins);
    legendInfo = legend;
    legendInfo{end+1} = ['Geant4 simulation for \lambda = ' num2str(lambda)];
    stairs(MeV2Volts(x_sim), smooth(y_sim, n_smooth), color)
end