function nplot
    N_bins = 200;
    
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
    x = zeros(N_bins, L);
    y = zeros(N_bins, L);
    legendInfo = cell(1,L);
    
    for i=1:L
        data = load(files{i});
        [counts, centers] = hist(data, N_bins);
        x(:,i) = centers.';
        y(:,i) = smooth(counts.', 1);
        
        [pathstr,name,ext] = fileparts(files{i});
        legendInfo{i} = name;
    end
    
    figure(1)
    stairs(x, y)
    legend(legendInfo)
    title('E_{primaries} = 2.5MeV')
    xlabel('E_{deposit}, MeV')
    ylabel('Counts')
end