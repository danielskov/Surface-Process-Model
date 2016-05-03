%function read_output()

clc
close all;
clear;

folder=sprintf('/weathchange/')

frame_mod=2;

%folder=sprintf('');
b=sprintf('%d',0);

v=str2num(b);
%a= ['./output/output' num2str(b) '.dat'];
a= ['./output' folder '/erosion_output/erosion_output' num2str(b)];
fud = fopen([a]);
nx=101;
ny=101;
dx=200;
dy=200;

X=linspace(0,nx*dx-dx,nx);
Y=linspace(0,ny*dy-dy,ny)';
X=(ones(ny,1)*X);
Y=(Y*ones(1,nx));

fId=figure;

do_long='n'
make_video='n'
%fclose(fud);
switch (make_video)
    case ('y')
        WriterObj=VideoWriter('Landscape Evolution','MPEG-4');
        WriterObj.FrameRate=4;
        open(WriterObj);
        
        WriterObj2=VideoWriter('Long profile evolution','MPEG-4');
        WriterObj2.FrameRate=4;
        open(WriterObj2);
        
        WriterObj3=VideoWriter('Change','MPEG-4');
        WriterObj3.FrameRate=4;
        open(WriterObj3);
end
i=0;
while (fud~=-1)
    i=i+frame_mod;
    if (i~=1)
        
        %v=v+bplus*frame_mod;
        v=i-1;
        b=sprintf('%d',v);
        
        %a= ['./output/output' num2str(b)];
        a= ['./output' folder '/erosion_output/erosion_output' num2str(b)];
        
        %a= ['./output/output' num2str(b) '.dat'];
        fud = fopen([a]);
        if (fud==-1)
            break
        end
        
    end
    
    smooth_erosion=fread(fud,[nx,ny],'double')';
    reciever_slope=fread(fud,[nx,ny],'double')';
    diff_erosion=fread(fud,[nx,ny],'double')';
    diff=fread(fud,[nx,ny],'double')';

    fclose(fud);
    
    
    figure(1)
    h=surf(X,Y,smooth_erosion/(dx*dy));
    set(gca,'fontsize',16)
    title(['Smooth Erosion , time: ' num2str(b)],'FontSize',18);
    %text(500,500,'Distance [km]','FontSize',16)
    %text(500,500,'Distance [km]','FontSize',16)
    xlabel('Distance [m]','FontSize',16)
    ylabel('Distance [m]','FontSize',16)
    %text(500,500,'Elevation [m]','FontSize',16)
    set(h,'LineStyle','none')
    colorbar;
    set(gca,'fontsize',16)
    axis equal
    view(2)
    caxis([0 3e-3]);
    box on
    
    figure(2)
    h=surf(X,Y,reciever_slope);
    set(gca,'fontsize',16)
    title(['Reciever slope']);
    %text(500,500,'Distance [km]','FontSize',16)
    %text(500,500,'Distance [km]','FontSize',16)
    xlabel('Distance [m]','FontSize',16)
    ylabel('Distance [m]','FontSize',16)
    %text(500,500,'Elevation [m]','FontSize',16)
    set(h,'LineStyle','none')
    colorbar;
    set(gca,'fontsize',16)
    axis equal
    view(2)
    %caxis([0 3e-3]);
    box on
        
     figure(3)
    h=surf(X,Y,diff_erosion);
    set(gca,'fontsize',16)
    title('diff Erosion ','FontSize',18);
    %text(500,500,'Distance [km]','FontSize',16)
    %text(500,500,'Distance [km]','FontSize',16)
    xlabel('Distance [m]','FontSize',16)
    ylabel('Distance [m]','FontSize',16)
    %text(500,500,'Elevation [m]','FontSize',16)
    set(h,'LineStyle','none')
    colorbar;
    set(gca,'fontsize',16)
    axis equal
    view(2)
    caxis([0 3e-3]);
    box on
    
    figure(4)
    h=surf(X,Y,diff);
    set(gca,'fontsize',16)
    title(['diff , time: ' num2str(b)],'FontSize',18);
    %text(500,500,'Distance [km]','FontSize',16)
    %text(500,500,'Distance [km]','FontSize',16)
    xlabel('Distance [m]','FontSize',16)
    ylabel('Distance [m]','FontSize',16)
    %text(500,500,'Elevation [m]','FontSize',16)
    set(h,'LineStyle','none')
    colorbar;
    set(gca,'fontsize',16)
    axis equal
    view(2)
    caxis([0 3e-3]);
    box on
    
    mean(diff(:));
    
    %xlim([0,nx*dx-dx]);
    %ylim([0,ny*dy-dy]);
    pause(0.000002)
end