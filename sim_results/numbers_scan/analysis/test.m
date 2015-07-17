function test
    N_bins = 1000;
    
    figure(1)
    hold on
    
    d1 = load('e1.csv');
    [y1, x1] = hist(d1, N_bins);
    plot(x1,y1/max(y1),'r')
    
    d2 = load('e2.csv');
    [y2, x2] = hist(d2, N_bins);
    plot(x2,y2/max(y2),'g')
    
    d2f = 2*d1;
    [y2f, x2f] = hist(d2f, N_bins);
    plot(x2f,y2f/max(y2f),'b')
    
    d3 = load('e3.csv');
    [y3, x3] = hist(d3, N_bins);
    plot(x3,y3/max(y3),'k')
    
    d3f = 3*d1;
    [y3f, x3f] = hist(d3f, N_bins);
    plot(x3f,y3f/max(y3f),'m')
    
    d10 = load('e10.csv');
    [y10, x10] = hist(d10, N_bins);
    plot(x10,y10/max(y10),'r')
    
    d10f = 10*d1;
    [y10f, x10f] = hist(d10f, N_bins);
    plot(x10f,y10f/max(y10f),'k')
       
    hold off
end