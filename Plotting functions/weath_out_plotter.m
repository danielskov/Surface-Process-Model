clear; close all; clc

load('split0_hi.mat')
load('split01_hi.mat')
load('split03_Hi.mat')
load('split05_hi.mat')
load('split07_hi.mat')
load('split09_hi.mat')
load('split10_hi.mat')



x=[1:17
    1:17];

H = bar(x)
xlim([0.5 1.5]);

a=[1 1 0
    0 0 0
    0 0 1
    0 1 0
    0 1 1
    1 0 0
    1 0 1
    1 1 1
    240/255 120/255 0
    64/255 0 128/255
    128/255 64/255 0
    0 64/255 0
    128/255 128/255 128/255
    128/255 128/255 1
    0 128/255 128/255
    128/255 0 0
    1 128/255 128/255];

for i=1:17
    set(H(i),'EdgeColor',a(i,:),'faceColor',a(i,:));
end


figure(15)
figure(14)
tilefigs
figure(14)

hold all

tt=mean_weath_list0(1):1e-6:mean_weath_list0(end);
pp = pchip(mean_weath_list0,mean_erosion_list0/max(mean_erosion_list0),tt);
p1=plot(mean_weath_list0, mean_erosion_list0/max(mean_erosion_list0),'ob','Markersize',20)
plot(tt,pp,'-b','LineWidth',2)
clear tt pp

%The fitting procedure here uses the pchip model, which is a piecewise
%cubic hermite interpolating polynomial. Produces a smoother result than a
%normal cubic spline, and no overshoots or oscillations.

tt=mean_weath_list01(1):1e-6:mean_weath_list01(end);
pp = pchip(mean_weath_list01,mean_erosion_list01/max(mean_erosion_list01),tt);
p2=plot(mean_weath_list01, mean_erosion_list01/max(mean_erosion_list01),'*r','Markersize',20)
plot(tt,pp,'-r','LineWidth',2)
clear tt pp

tt=mean_weath_list03(1):1e-6:mean_weath_list03(end);
pp = pchip(mean_weath_list03,mean_erosion_list03/max(mean_erosion_list03),tt);
p3=plot(mean_weath_list03, mean_erosion_list03/max(mean_erosion_list03),'+g','Markersize',20)
plot(tt,pp,'-g','LineWidth',2)
clear tt pp

tt=mean_weath_list05(1):1e-6:mean_weath_list05(end);
pp = pchip(mean_weath_list05,mean_erosion_list05/max(mean_erosion_list05),tt);
p4=plot(mean_weath_list05, mean_erosion_list05/max(mean_erosion_list05),'xm','Markersize',20)
plot(tt,pp,'-m','LineWidth',2)
clear tt pp

tt=mean_weath_list07(1):1e-6:mean_weath_list07(end);
pp = pchip(mean_weath_list07,mean_erosion_list07/max(mean_erosion_list07),tt);
p5=plot(mean_weath_list07, mean_erosion_list07/max(mean_erosion_list07),'sc','Markersize',20)
plot(tt,pp,'-c','LineWidth',2)
clear tt pp

tt=mean_weath_list09(1):1e-6:mean_weath_list09(end);
pp = pchip(mean_weath_list09,mean_erosion_list09/max(mean_erosion_list09),tt);
p6=plot(mean_weath_list09, mean_erosion_list09/max(mean_erosion_list09),'d','color',a(9,:),'Markersize',20)
plot(tt,pp,'color',a(9,:),'LineWidth',2)
clear tt pp


tt=mean_weath_list10(1):1e-6:mean_weath_list10(end);
pp = pchip(mean_weath_list10,mean_erosion_list10/max(mean_erosion_list10),tt);
p7=plot(mean_weath_list10, mean_erosion_list10/max(mean_erosion_list10),'pk','Markersize',20)
plot(tt,pp,'-k','LineWidth',2)


clear tt pp

h=legend([p1 p2 p3 p4 p5 p6 p7],{'100% S-A','90% S-A','70% S-A','50% S-A','30% S-A','10% S-A','0% S-A'})
set(h,'FontSize',26,'Location','SouthEast')

ylabel('Normalized steady state fluvial incision rate','FontSize',26)
xlabel('Maximum weathering rate [m/yr]','FontSize',26)
set(gca,'FontSize',26)

xlim([0 1e-3])
savefig(figure(14),'weathfig.fig');
print(figure(14),'weathfig','-depsc');





figure(15)
hold all

tt=mean_weath_list0(1):1e-6:mean_weath_list0(end);
pp = pchip(mean_weath_list0,mean_erosion_list0,tt);
p1=plot(mean_weath_list0, mean_erosion_list0,'ob','Markersize',20)
plot(tt,pp,'-b','LineWidth',2)
clear tt pp


tt=mean_weath_list01(1):1e-6:mean_weath_list01(end);
pp = pchip(mean_weath_list01,mean_erosion_list01,tt);
p2=plot(mean_weath_list01, mean_erosion_list01,'*r','Markersize',20)
plot(tt,pp,'-r','LineWidth',2)
clear tt pp


tt=mean_weath_list03(1):1e-6:mean_weath_list03(end);
pp = pchip(mean_weath_list03,mean_erosion_list03,tt);
p3=plot(mean_weath_list03, mean_erosion_list03,'+g','Markersize',20)
plot(tt,pp,'-g','LineWidth',2)
clear tt pp

tt=mean_weath_list05(1):1e-6:mean_weath_list05(end);
pp = pchip(mean_weath_list05,mean_erosion_list05,tt);
p4=plot(mean_weath_list05, mean_erosion_list05,'xm','Markersize',20)
plot(tt,pp,'-m','LineWidth',2)
clear tt pp

tt=mean_weath_list07(1):1e-6:mean_weath_list07(end);
pp = pchip(mean_weath_list07,mean_erosion_list07,tt);
p5=plot(mean_weath_list07, mean_erosion_list07,'sc','Markersize',20)
plot(tt,pp,'-c','LineWidth',2)

clear tt pp

tt=mean_weath_list09(1):1e-6:mean_weath_list09(end);
pp = pchip(mean_weath_list09,mean_erosion_list09,tt);
p6=plot(mean_weath_list09, mean_erosion_list09,'d','color',a(9,:),'Markersize',20)
plot(tt,pp,'color',a(9,:),'LineWidth',2);
clear tt pp


tt=mean_weath_list10(1):1e-6:mean_weath_list10(end);
pp = pchip(mean_weath_list10,mean_erosion_list10,tt);
p7=plot(mean_weath_list10, mean_erosion_list10,'pk','Markersize',20)
plot(tt,pp,'-k','LineWidth',2)
clear tt pp

%The fitting procedure here uses the pchip model, which is a piecewise
%cubic hermite interpolating polynomial. Produces a smoother result than a
%normal cubic spline, and no overshoots or oscillations.
ylabel('Fluvial incision rate [m/yr]','FontSize',26)
xlabel('Maximum weathering rate [m/yr]','FontSize',26)
set(gca,'FontSize',26)
h=legend([p1 p2 p3 p4 p5 p6 p7],{'100% S-A','90% S-A','70% S-A','50% S-A','30% S-A','10% S-A','0% S-A'})
set(h,'FontSize',26,'Location','SouthEast')
%xlim([0 1e-3])
savefig(figure(14),'weathfig.fig');

pause(2)
path='/Users/danielss/Dropbox (ICE Research Group)/Ph.d. mappe/Article Fall 2015/weath_erosion.eps';
%saveas(figure(15),path)
