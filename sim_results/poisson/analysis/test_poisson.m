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

        y(:,i) = smooth(counts.', 5);
        
        [pathstr, name, ext] = fileparts(files{i});
        legendInfo{i} = name;
    end
    
    [x_sim, y_sim] = g4poisson(4.2, 1e4, N_bins);
    legendInfo{end+1} = 'Geant4 simulation for \lambda = 4.2';
    
    figure(1)
    stairs(x, y)
    hold on
        stairs(MeV2Volts(x_sim), smooth(y_sim, 5), 'r')
    hold off
    legend(legendInfo)
    xlabel('Amplitude, V')
    ylabel('Counts')
end

function y = MeV2Volts(x)
%     k = 255 / 2.88 / 4
    y = x / 0.226 * 0.012;
end