%function read_output()

close all;
clear all;

folder=sprintf('/streampower/')
folder=sprintf('/2_streamstart2_wlandslidesandcrit/')
%folder=sprintf('/3_weath1.0/')
%folder=sprintf('/4_lowuplift_nolandslides_split0.0/')
folder=sprintf('/3_towardssteadystate_split0.0/')
folder=sprintf('/4_lowuplift_nolandslides_split0.0/')
folder=sprintf('/4_nouplift_highertaucrit/')
folder=sprintf('/4_lowuplift_nolandslides_split0.0/')
folder=sprintf('/4_lowuplift_nolandslid_higher_k_diff/')
folder=sprintf('/4_high_diff_taucrit_sedload/')
folder=sprintf('/new_sedcap/')
folder=sprintf('/4_highertaucrit_ksed/')
%folder=sprintf('/4_evenhigher_taucrit/')


%folder=sprintf('');
b=sprintf('%014.2f',0);
v=str2num(b);
%a= ['./output/output' num2str(b) '.dat'];
a= ['./output' folder '/output' num2str(b)];
fud = fopen([a]);
nx=fread(fud,1,'int64');
ny=fread(fud,1,'int64');
dx=fread(fud,1,'double');
dy=fread(fud,1,'double');
step=fread(fud,1,'double');
print_modulo=fread(fud,1,'double');
n_outputs=fread(fud,1,'double');
deltat=fread(fud,1,'double');
bplus=deltat*print_modulo;

X=linspace(0,nx*dx-dx,nx);
Y=linspace(0,ny*dy-dy,ny)';
X=(ones(ny,1)*X);
Y=(Y*ones(1,nx));
bed=0;
t=1;
%break

fId=figure;

do_long='y'
make_video='y'
%fclose(fud);
switch (make_video)
    case ('y')
WriterObj=VideoWriter('Landscape Evolution','MPEG-4');
WriterObj.FrameRate=4;
open(WriterObj);

WriterObj2=VideoWriter('Long profile evolution','MPEG-4');
WriterObj2.FrameRate=4;
open(WriterObj2);
end
sum_landslide_erosion=zeros(ny,nx);

%nx=0;
%ny=0;

frame_mod=1;
for i=1:n_outputs/frame_mod+1
    
    if (i~=1)
    v=v+bplus*frame_mod;
    b=sprintf('%014.2f',v);
    %a= ['./output/output' num2str(b)];
    a= ['./output' folder '/output' num2str(b)];

    %a= ['./output/output' num2str(b) '.dat'];
    fud = fopen([a]);
    
    bed_before=bed;
    nx=fread(fud,1,'int64');
    ny=fread(fud,1,'int64');
    dx=fread(fud,1,'double');
    dy=fread(fud,1,'double');
    step=fread(fud,1,'double');
    print_modulo=fread(fud,1,'double');
    %print_modulo=29;
    n_outputs=fread(fud,1,'double');
    deltat=fread(fud,1,'double');
    end
    n_pits = fread(fud,1,'int64')';
    av_height=fread(fud,1,'double');
    max_height=fread(fud,1,'double');
    av_incision=fread(fud,1,'double');
    landslides_since_last=fread(fud,1,'int64');
    bed = fread(fud,[nx,ny],'double')';
    topsedi=fread(fud,[nx,ny],'double')';
    id = fread(fud,[nx,ny],'int64')';
    reciever = fread(fud,[nx,ny],'int64')';
    drain_area=fread(fud,[nx,ny],'double')';
    reciever_distance=fread(fud,[nx,ny],'double')';
    erosion=fread(fud,[nx,ny],'double')';
    fluv=fread(fud,[nx,ny],'double')';
    diff=fread(fud,[nx,ny],'double')';
    fluv_over_diff=fread(fud,[nx,ny],'double')';
    rel_sedi=fread(fud,[nx,ny],'double')';
    sediment_capa=fread(fud,[nx,ny],'double')';
    stream_power=fread(fud,[nx,ny],'double')';
    channel_width=fread(fud,[nx,ny],'double')';
    reciever_bed_height=fread(fud,[nx,ny],'double')';
    reciever_reciever_bed_height=fread(fud,[nx,ny],'double')';
    upstream_erosion=fread(fud,[nx,ny],'double')';
    landslide_erosion=fread(fud,[nx,ny],'double')';
    reciever_slope=fread(fud,[nx,ny],'double')';
    moved_sediment=fread(fud,[nx,ny],'double')';
    landslide_deposition=fread(fud,[nx,ny],'double')';
    fluvial_deposition=fread(fud,[nx,ny],'double')';
    in_stack=fread(fud,[nx,ny],'int64')';
    total_landslide_erosion=fread(fud,[nx,ny],'double')';
    river=fread(fud,[nx,ny],'double')';

    fclose(fud);

    
    
    num_plots_x=5;
    num_plots_y=2;
    
    figure(fId)
    set(gcf, 'Position', [200, 100, 1000,700]);
    %set(gcf, 'Position', [200, 100, 1800,1200]);

    %subplot(2,5,1)
    %subplot('Position',[0.03 0.01 0.16 0.45]);
    subplot('Position',[(0/num_plots_x+0.03) (0/num_plots_y+0.01) (1/num_plots_x-0.04) (1/num_plots_y-0.05)]); 
    h=surf(X,Y,river);
    set(h,'LineStyle','none')
    caxis([0 max(river(:))+1e-8]);
    set(h,'edgecolor','none','Linestyle','none','FaceLighting','phong');
    title(['Fluvial evolution, time: ' num2str(v) ' npits: ' num2str(n_pits) ' n=1'],'FontSize',30);
    %title('Bed height')
    xlabel('x','FontSize',30);
    ylabel('y','FontSize',30);
    zlabel('height','FontSize',30);
    xlim([0,nx*dx-dx]);
    ylim([0,ny*dy-dy]);
    colorbar
    %axis equal
    view(2)
 %  frame=getframe(gcf);
 %  writeVideo(WriterObj,frame);
   
    subplot('Position',[1/num_plots_x+0.03 0/num_plots_y+0.01 1/num_plots_x-0.04 1/num_plots_y-0.05]); 
    h=surf(X,Y,topsedi);
    set(h,'LineStyle','none')
    colorbar;
    %axis equal
    view(2)
    caxis([0 max(topsedi(:))]);
    xlim([0,nx*dx-dx]);
    ylim([0,ny*dy-dy]);
    title('topsedi')
 
    

    
    %subplot(2,5,3)
    %subplot('Position',[0.43 0.01 0.16 0.45]);
    subplot('Position',[3/num_plots_x+0.03 0/num_plots_y+0.01 1/num_plots_x-0.04 1/num_plots_y-0.05]); 
    h=surf(X,Y,abs(reciever_slope));
    set(h,'LineStyle','none')
    colorbar;
    %axis equal
    view(2)
        caxis([0 abs(min(reciever_slope(:)))]);
    %caxis([0 0.55]);
    xlim([0,nx*dx-dx]);
    ylim([0,ny*dy-dy]);
    title('reciever slope')
    
    %subplot(2,5,4)
    %subplot('Position',[0.63 0.01 0.16 0.45]);
    subplot('Position',[4/num_plots_x+0.03 0/num_plots_y+0.01 1/num_plots_x-0.04 1/num_plots_y-0.05]); 
    h=surf(X,Y,diff);
    set(h,'LineStyle','none')
    colorbar;
    %axis equal
    view(2)
    caxis([min(diff(:))-1e-14 max(diff(:))+1e-8]);
    xlim([0,nx*dx-dx]);
    ylim([0,ny*dy-dy]);
    title('Diff')
    
    %subplot(2,5,5)
    %subplot('Position',[0.83 0.01 0.16 0.45]);
    subplot('Position',[2/num_plots_x+0.03 1/num_plots_y+0.01 1/num_plots_x-0.04 1/num_plots_y-0.05]);  
    h=surf(X,Y,rel_sedi);
    set(h,'LineStyle','none')   
    colorbar;
    %axis equal
    view(2)
    caxis([0 1]);
    xlim([0,nx*dx-dx]);
    ylim([0,ny*dy-dy]);
    title('Rel sedi')
    
    
 
    
    %subplot(2,5,6)
    %subplot('Position',[0.03 0.51 0.16 0.45]);
    subplot('Position',[0/num_plots_x+0.03 1/num_plots_y+0.01 1/num_plots_x-0.04 1/num_plots_y-0.05]); 
    h=surf(X,Y,sediment_capa);
    set(h,'LineStyle','none')   
    colorbar;
    %axis equal
    view(2)
    caxis([0 max(sediment_capa(:))+1e-8]);
    xlim([0,nx*dx-dx]);
    ylim([0,ny*dy-dy]);
    title('Sediment capa')
    
    %log_ero=log((1+fluv+diff))/log((1+max(fluv(:))));
    ero=fluv+diff;
    %subplot(2,5,7)
   
    
    subplot('Position',[0.23 0.51 0.16 0.45]);
    subplot('Position',[1/num_plots_x+0.03 1/num_plots_y+0.01 1/num_plots_x-0.04 1/num_plots_y-0.05]); 
    %h=surf(X,Y,%close all);
    h=surf(X,Y,erosion)
    set(h,'LineStyle','none')   
    colorbar;
    %axis equal
    view(2)
    caxis([0 max(erosion(:))+1e-8]);
    xlim([0,nx*dx-dx]);
    ylim([0,ny*dy-dy]);
    title('Total erosion')
    
    %{
    %subplot('Position',[0.23 0.51 0.16 0.45]);
    subplot('Position',[1/num_plots_x+0.03 1/num_plots_y+0.01 1/num_plots_x-0.04 1/num_plots_y-0.05]); 
    h=surf(X,Y,in_stack);
    set(h,'LineStyle','none')   
    colorbar;
    %axis equal
    view(2)
    caxis([0 1]);
    xlim([0,nx*dx-dx]);
    ylim([0,ny*dy-dy]);
    title('In stack')
    %}

    %subplot(2,5,9)
    %subplot('Position',[0.63 0.51 0.16 0.45]);
    subplot('Position',[3/num_plots_x+0.03 1/num_plots_y+0.01 1/num_plots_x-0.04 1/num_plots_y-0.05]); 
    h=surf(X,Y,fluv-stream_power);
    set(h,'LineStyle','none')   
    colorbar;
    %axis equal
    view(2)
    sed_incision=fluv-stream_power;
    caxis([0 max(sed_incision(:))+1e-8]);
    xlim([0,nx*dx-dx]);
    ylim([0,ny*dy-dy]);
    title('Sed_incision')
    
    %subplot(2,5,10)
    %subplot('Position',[0.83 0.51 0.16 0.45]);
    subplot('Position',[4/num_plots_x+0.03 1/num_plots_y+0.01 1/num_plots_x-0.04 1/num_plots_y-0.05]); 
    sediment_thickness=topsedi-bed;
    h=surf(X,Y,sediment_thickness);
    set(h,'LineStyle','none')   
    colorbar;
    %axis equal
    view(2)
    caxis([0 max(sediment_thickness(:))+1e-8]);
    xlim([0,nx*dx-dx]);
    ylim([0,ny*dy-dy]);
    title('Sediment thickness')
    
    
       %subplot(2,5,5)
    %subplot('Position',[0.83 0.01 0.16 0.45]);
    subplot('Position',[2/num_plots_x+0.03 0/num_plots_y+0.01 1/num_plots_x-0.04 1/num_plots_y-0.05]);  
    h=surf(X,Y,moved_sediment);
    set(h,'LineStyle','none')   
    colorbar;
    %axis equal
    view(2)
    caxis([0 max(moved_sediment(:))]);
    xlim([0,nx*dx-dx]);
    ylim([0,ny*dy-dy]);
    title('Moved sediment')
        
    subplot('Position',[2/num_plots_x+0.03 1/num_plots_y+0.01 1/num_plots_x-0.04 1/num_plots_y-0.05]);  
    h=surf(X,Y,drain_area);
    set(h,'LineStyle','none')   
    colorbar;
    %axis equal
    view(2)
    caxis([0 max(drain_area(:))]);
    xlim([0,nx*dx-dx]);
    ylim([0,ny*dy-dy]);
    title('drain area')
    

    
        disp('Landslide erosion-other erosion');
    sum(landslide_erosion(:))-sum(ero(:))
    
    
    %{
    if (i==5)
        j=floor(2*nx/3); 
        h=floor(2*ny/3);
        k=0;
        yes=0;
        while (yes==0)
            k=k+1
            if rel_sedi(j,h)<1
                yes=1;
            else
               if (mod(k,2)==0 && h<nx)
                   h=h+1;
               elseif (j<ny)
                   j=j+1;
               else
                disp('lol vi er paa kanten')
                return
               end
            end
        end
        [exhaus,fluv_inc,stream_pow_,diffusion_]=exhaustive_search(rel_sedi(j,h),bed,reciever_bed_height(j,h),reciever_reciever_bed_height(j,h),reciever_distance(j,h),sediment_capa(j,h),deltat,channel_width(j,h),upstream_erosion(j,h),bed_before(j,h),drain_area(j,h));
        break
    end
    
    
    figure(2)
    set(gcf, 'Position', [200, 100, 1000, 800]);
    h=surf(X,Y,bed);
    set(h,'LineStyle','none')
    caxis([0 6]);
    set(h,'edgecolor','none','Linestyle','none','FaceLighting','phong');
    title(['Fluvial evolution, time: ' num2str(b) ' npits: ' num2str(n_pits) ' n=2'],'FontSize',30);
    xlabel('x','FontSize',30);
    ylabel('y','FontSize',30);
    zlabel('height','FontSize',30);
    colorbar
    %axis equal
    view(2)
    %}
    
    figure(5)
    h=surf(X,Y,topsedi);
    set(gca,'fontsize',16)
    %title(['Fluvial evolution, time: ' num2str(v)],'FontSize',18);
    %text(500,500,'Distance [km]','FontSize',16)
    %text(500,500,'Distance [km]','FontSize',16)
    xlabel('Distance [m]','FontSize',16)
    ylabel('Distance [m]','FontSize',16)
    %text(500,500,'Elevation [m]','FontSize',16)
    set(h,'LineStyle','none')
    colorbar;
    set(gca,'fontsize',16)
    axis equal
    text(600,600,'Elevation [m]','FontSize',16)
    view(2)
    caxis([0 max(topsedi(:))]);
    box on
    %xlim([0,nx*dx-dx]);
    %ylim([0,ny*dy-dy]);

 switch (make_video)
   case ('y')
   frame=getframe(figure(5));
   writeVideo(WriterObj,frame);
 end
 
 switch(do_long)
        case 'y'
        long_profile=[];
        distance=[];
        drain_area_=[];
        
        if n_pits==0
        if (t==1)
            [k,d] = find(topsedi==max(topsedi(:)));
            if (length(k)>1)
                k=k(1);
                d=d(1);
            end
            t=2;
        end
    
            j=1;
            long_profile(j)=topsedi(k,d);
            drain_area_(j)=drain_area(k,d);
            distance(j)=0;
            [r,c] = find(id==reciever(k,d));
            while (topsedi(r,c)>=0)
            j=j+1;
            distance(j)=reciever_distance(r,c);
            drain_area_(j)=drain_area(r,c);
            n=r; u=c;
            [r,c]=find(id==reciever(r,c));
            long_profile(j)=topsedi(r,c);
            if n==r && u==c break
            end
                if j>(nx*ny)
                    disp('fejl')
                    return;
                end
            end
        end
        cumsumdistance=cumsum(distance);
        figure(4)
        plot(cumsumdistance,long_profile)

        %hold on
        %plot(cumsumdistance,long_profile/max(long_profile(:)))
        %plot(cumsumdistance,drain_area_/max(drain_area(:)))
 end
 
 switch (make_video)
    case ('y')
    frame=getframe(figure(4));
   writeVideo(WriterObj2,frame);
 end
 
 figure(6)
 hold on
 plot(step,av_height,'b*')
 plot(step,max_height,'r*')
 legend('av height','max height')
 
 figure(7)
 hold on
 plot(step,av_incision,'*r')
 title('av incision')
 
 figure(8)
 hold on
 plot(step,landslides_since_last,'*r')
 title('landslides since last')
 
   step_recorder(i)=step;
   sum_sediment_flux_out(i)=sum(upstream_erosion(1,:));
   sed_flux_out(i,:)=upstream_erosion(1,:);
    pause(0.002)
end

switch (make_video)
    case ('y')
close(WriterObj);
close(WriterObj2);
end

figure(10)
plot(step_recorder,sum_sediment_flux_out,'-')
%hold on
plot([0 max(step_recorder)],[4e-3*dx*dy*nx*ny 4e-3*dx*dy*nx*ny])
figure(11)
plot(step_recorder,sed_flux_out,'-')


%{
long_profile=[];
distance=[];

[b,d] = find(bed==max(bed(:)));
if (length(r)>1)
    r=r(1);
    c=c(1);
end
j=1;
long_profile(j)=bed(b,d);
distance(j)=0;
[r,c] = find(id==reciever(b,d));
while (bed(r,c)>min(bed(:)))
    j=j+1
    long_profile(j)=bed(r,c);
    distance(j)=reciever_distance(r,c);
    [r,c]=find(id==reciever(r,c));
    if j>(nx*ny)
        disp('fejl')
        return;
    end
end

cumsumdistance=cumsum(distance);
figure
plot(cumsumdistance,long_profile)
%}
    
long_profile=[];
drain_area_=[];
distance=[];

[r,c] = find(topsedi==max(topsedi(:)));
if (length(r)>1)
    r=r(1);
    c=c(1);
end
j=1;
long_profile(j)=topsedi(r,c);
drain_area_(j)=drain_area(r,c);
sediment(j)=upstream_erosion(r,c);
distance(j)=0;
[r,c] = find(id==reciever(r,c));
while (bed(r,c)>min(topsedi(:)))
    j=j+1
    distance(j)=reciever_distance(r,c);
    drain_area_(j)=drain_area(r,c);
    sediment(j)=upstream_erosion(r,c);
    [r,c]=find(id==reciever(r,c));
    long_profile(j)=topsedi(r,c);
    if j>(nx*ny)
        disp('fejl')
        return;
    end
end

cumsumdistance=cumsum(distance);
figure(12)
plot(cumsumdistance,long_profile/max(long_profile(:)))
hold on
plot(cumsumdistance,drain_area_/max(drain_area(:)))
plot(cumsumdistance,sediment/max(sediment(:)))

legend('long profile','drainage area','sediment')
    