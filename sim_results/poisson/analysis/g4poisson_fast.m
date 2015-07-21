function [x, y] = g4poisson_fast(lambda, n_events, n_bins, sim_data)
    N_max_electrons = 10;
    coefs = poisspdf(1:N_max_electrons, lambda);
    
    data = zeros(1, n_events);
    
    counter = 1;
    for i=1:N_max_electrons
        n_current_events = floor(n_events * coefs(i));
        i_end = counter + n_current_events;
        
        data(counter:i_end-1) = MeV2Volts(g4load(i, n_current_events, sim_data));
        
        counter = i_end;
    end
    data(counter:end) = g4load(0, n_events - counter + 1);
    
    [y, x] = hist(data, n_bins);
end

function deposit_energies = g4load(n_electrons, n_events, sim_data)
    if (n_electrons > 0) && (n_electrons <= 10)
        data = sim_data{n_electrons};
    else
        data = normrnd(0, 2e-3*18.7, n_events, 1);
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