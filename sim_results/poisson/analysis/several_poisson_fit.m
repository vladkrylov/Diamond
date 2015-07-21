function several_poisson_fit
    x_centers = 0:1e-3:0.35;
    exp_data = load('../expdata__Run16__Beamtime5.csv') - 0.003;
    y_exp = hist(exp_data, x_centers);
    y_exp = smooth(y_exp, 5).';
    
    sim_data = sim_load_map();
    
    options = optimset('Display', 'iter',...
                       'MaxFunEvals', 1e3,...
                       'TolX', 1e-9);
    lambdas0 = [1, 1, 1
                2.9, 0.5, 1.2];
%     pfit(lambdas0, y_exp, x_centers);
    x = fminsearch(@(x)pfit(x, y_exp, x_centers, sim_data), lambdas0, options)
    close all;
    pfit(x, y_exp, x_centers, sim_data)
end

function r = pfit(par, exp_data, x_centers, sim_data)
    amps = par(1,:);
    amps(amps < 0) = 1;
    lambdas = par(2,:);
    lambdas(lambdas < 0) = 0;

    n_posissons = length(lambdas);
    n_points = length(x_centers);
    
    x_sim = zeros(n_posissons, n_points);
    y_sim = zeros(n_posissons, n_points);
    
    for i=1:n_posissons
        [x_sim(i,:), y_sim(i,:)] = g4poisson_fast(lambdas(i), 1e5, x_centers, sim_data);
        y_sim(i,:) = smooth(y_sim(i,:), 5);
    end
    
    
    y = sum(diag(amps) * y_sim, 1);
    r = sum((y-exp_data).^2 / n_points);
    
%     figure(1)
%     hold on
%         stairs(x_centers, exp_data, 'b');
%         stairs(x_centers, y, 'r');
%     hold off
end

function sim_data = sim_load_map()
    sim_data = cell(1,10);
    sim_data{1} = load('../../numbers_scan_2.5MeV/e1.csv');
    sim_data{2} = load('../../numbers_scan_2.5MeV/e2.csv');
    sim_data{3} = load('../../numbers_scan_2.5MeV/e3.csv');
    sim_data{4} = load('../../numbers_scan_2.5MeV/e4.csv');
    sim_data{5} = load('../../numbers_scan_2.5MeV/e5.csv');
    sim_data{6} = load('../../numbers_scan_2.5MeV/e6.csv');
    sim_data{7} = load('../../numbers_scan_2.5MeV/e7.csv');
    sim_data{8} = load('../../numbers_scan_2.5MeV/e8.csv');
    sim_data{9} = load('../../numbers_scan_2.5MeV/e9.csv');
    sim_data{10} = load('../../numbers_scan_2.5MeV/e10.csv');
end