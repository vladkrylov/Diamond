function [x, y] = g4poisson(lambda, n_events, n_bins)
    N_max_electrons = 10;
    coefs = poisspdf(1:N_max_electrons, lambda);
    
    data = zeros(1, n_events);
    
    counter = 1;
    for i=1:N_max_electrons
        n_current_events = floor(n_events * coefs(i));
        i_end = counter + n_current_events;
        
        data(counter:i_end-1) = g4load(i, n_current_events);
        
        counter = i_end;
    end
    data(counter:end) = g4load(0, n_events - counter + 1);
    
    [y, x] = hist(data, n_bins);
end

function deposit_energies = g4load(n_electrons, n_events)
    switch n_electrons
        case 0
            data = normrnd(0, 1e-3*18.7, n_events, 1);
        case 1
            data = load('../../numbers_scan_2.5MeV/e1.csv');
        case 2
            data = load('../../numbers_scan_2.5MeV/e2.csv');
        case 3
            data = load('../../numbers_scan_2.5MeV/e3.csv');
        case 4
            data = load('../../numbers_scan_2.5MeV/e4.csv');
        case 5
            data = load('../../numbers_scan_2.5MeV/e5.csv');
        case 6
            data = load('../../numbers_scan_2.5MeV/e6.csv');
        case 7
            data = load('../../numbers_scan_2.5MeV/e7.csv');
        case 8
            data = load('../../numbers_scan_2.5MeV/e8.csv');
        case 9
            data = load('../../numbers_scan_2.5MeV/e9.csv');
        case 10
            data = load('../../numbers_scan_2.5MeV/e10.csv');
        otherwise
            data = zeros(n_events, 1);
    end
    
    N_loaded_events = size(data, 1);
    N =  idivide(uint32(n_events), uint32(N_loaded_events));
    rem = mod(n_events, N_loaded_events);
    
    deposit_energies = zeros(1, n_events);
    for i=1:N
        deposit_energies(N_loaded_events*(i-1)+1:N_loaded_events*i) = data;
    end
    deposit_energies(N*N_loaded_events+1:end) = data(1:rem);
end