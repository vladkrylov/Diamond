function testMeV
    N_bins = 1000;
    
    figure(1)
    hold on
    
    d2 = load('../2MeV.csv');
    [y2, x2] = hist(d2, N_bins);
    stairs(x2,y2/max(y2),'r')
    
    d4 = load('../4MeV.csv');
    [y4, x4] = hist(d4, N_bins);
    stairs(x4,y4/max(y4),'g')
    
    d8 = load('../8MeV.csv');
    [y8, x8] = hist(d8, N_bins);
    stairs(x8,y8/max(y8),'b')
    
    d16 = load('../16MeV.csv');
    [y16, x16] = hist(d16, N_bins);
    stairs(x16,y16/max(y16),'m')
       
    hold off
end