function nplot
    N_bins = 500;
    
    files = {
        '../e1.csv'...
        ,'../e2.csv'...
        ,'../e3.csv'...
        ,'../e4.csv'...
        ,'../e5.csv'...
        ,'../e6.csv'...
        ,'../e7.csv'...
        ,'../e8.csv'...
        ,'../e9.csv'...
        ,'../e10.csv'...
        };
    
    L = length(files);
    x = zeros(N_bins+1, L);
    y = zeros(N_bins+1, L);
    legendInfo = cell(1,L);
    
    for i=1:L
        data = load(files{i});
        [counts, centers] = hist(data, 0:7/N_bins:7);
        x(:,i) = centers.';
        y(:,i) = smooth(counts.', 1);
        
        [pathstr,name,ext] = fileparts(files{i});
        legendInfo{i} = name;
    end
    
    % add expenrimental data
    data = load('../../poisson/expdata__Run16__Beamtime5.csv');
    [counts, centers] = hist(data, 300);
    x_exp = Volt2MeV(centers.' - 0.0034);
    y_exp = 1e2*smooth(counts.', 5);
    
    figure(1)
    stairs(x, y)
    hold on
        stairs(x(:,1), sum(y,2))
        stairs(x_exp, y_exp, 'k')
    hold off
    legend(legendInfo)
    title('E_{primaries} = Gauss(mean = 2.5MeV, sigma = 0.2MeV)')
    xlabel('E_{deposit}, MeV')
    ylabel('Counts')
end

function y = Volt2MeV(x)
    y = x / 0.012 * 0.226;
end