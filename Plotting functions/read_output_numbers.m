%function read_output()

clc
close all;
clear;

for jjj=1:1
    clear step_list;
    clear mean_small;
    clear mean_large;
    clear length_I_list;
    clear length_J_list;
    
    folder=sprintf('/newstart/')
    folder=sprintf('/after_newstart/')
    folder=sprintf('/notimechange/')
    folder=sprintf('/stopuplift_onlydown/')
    %folder=sprintf('/stopuplift_onlyup/')
    folder=sprintf('/onlydown/')
    folder=sprintf('/onlyup/')
    folder=sprintf('/onlydown_1MA/')
    %folder=sprintf('/onlyup_1MA/')
    %folder=sprintf('/streampower/')
    %folder=sprintf('/streampower_wsedi/')
    %folder=sprintf('/streampower_wsedi_long/')
    folder=sprintf('/test/')
    %folder=sprintf('/test2/')
    %folder=sprintf('/difftest/')
    folder=sprintf('/newstart_lowparameters/')
    folder=sprintf('/newstart_lowparameters2/')
folder=sprintf('/onlyup_1MA_new_moreoutput/')
folder=sprintf('/test/')

    frame_mod=1;
    
    
    
    %folder=sprintf('');
    b=sprintf('%014.2f',0);
    v=str2num(b);
    %a= ['./output/output' num2str(b) '.dat'];
    a= ['../output' folder '/output' num2str(b)];
    fud = fopen([a]);
    nx=fread(fud,1,'int64');
    ny=fread(fud,1,'int64');
    dx=fread(fud,1,'double');
    dy=fread(fud,1,'double');
    old_step=0;
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
    sum_total_landslide_erosion_old=0;
    t=1;
    %break
    
    fId=figure;
    
    do_long='y'
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
    smooth_erosion=zeros(ny,nx);
    %nx=0;
    %ny=0;
    
    %for i=1:n_outputs/frame_mod+1
    i=2;
    i_start=i;
    counter=0;
    while (fud~=-1)
        i=i+frame_mod;
        counter=counter+1;
        %i=18;
        %i=40;
%         i=400;
%         i=370;
%         i=340;
%         i=423;
%         i=350;
%         i=355;
%         %i=354
        v=i-1;
        b=sprintf('%014.2f',v);
        %a= ['./output/output' num2str(b)];
        a= ['../output' folder '/output' num2str(b)];
        
        %a= ['./output/output' num2str(b) '.dat'];
        fud = fopen([a]);
        if (fud==-1)
            break
        end
        
        
        [bed_before,smooth_erosion_before,nx,ny,dx,dy,old_step,step,print_modulo,n_outputs,deltat,n_pits,av_height,max_height,av_incision,landslides_since_last,bed,topsedi,id,reciever,drain_area,reciever_distance,erosion,av_erosion,fluv,diff,fluv_over_diff,rel_sedi,sediment_capa,stream_power,channel_width,reciever_bed_height,reciever_reciever_bed_height,upstream_erosion,landslide_erosion,reciever_slope,moved_sediment,landslide_deposition,fluvial_deposition,in_stack,total_landslide_erosion,river,sediment_thickness2,deflection,smooth_erosion,di,catchment,smooth_relsedi,smooth_diff,smooth_saltabr,smooth_streampower,sed_incision] = read_parameters(fud,bed,smooth_erosion,step);
        
        large_plot(fId,X,Y,river,step,n_pits,dx,dy,topsedi,landslide_deposition,moved_sediment,sediment_thickness2,total_landslide_erosion,reciever_slope,rel_sedi,fluvial_deposition,sediment_capa,fluv,diff,erosion,in_stack,stream_power,nx,ny,sed_incision,bed)

        
            hFig = figure(5);
    set(gcf, 'Position', [1200, 1100, 1000,700]);
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
    title(['Time: ' num2str(step) ' years'],'FontSize',30);
    %view(2)
    caxis([0 max(topsedi(:))]);
    %caxis([0 5000]);
    %caxis([0 2600]);
        
        %{
    

    
        disp('Landslide erosion-other erosion');
    sum(landslide_erosion(:))-sum(ero(:))
    
    
        
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
        
    


    view(30,45)
    box on
    %xlim([0,nx*dx-dx]);
    %ylim([0,ny*dy-dy]);
    
    J=find(river==0);
    rel_sedi(J)=0;
    figure(4485)
    h=surf(X,Y,rel_sedi);
    set(gca,'fontsize',16)
    title('Rel sedi');
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
    caxis([0 1]);
    box on
    %xlim([0,nx*dx-dx]);
    %ylim([0,ny*dy-dy]);
    
    figure(5232)
    h=surf(X,Y,erosion/(dx*dy));
    set(gca,'fontsize',16)
    title(['Erosion , time: ' num2str(step)],'FontSize',18);
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
   % caxis([0 max(topsedi(:))]);
    box on
    %xlim([0,nx*dx-dx]);
    %ylim([0,ny*dy-dy]);
    
    
    
    %pause(2)
    
    figure(555)
    h=surf(X,Y,topsedi*4,sediment_thickness);
    set(gca,'fontsize',16)
    title('sedthick on topsedi');
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
    %caxis([0 max(topsedi(:))]);
    box on
    %xlim([0,nx*dx-dx]);
    %ylim([0,ny*dy-dy]);

    
    figure(6485)
    h=surf(X,Y,deflection);
    set(gca,'fontsize',16)
    title('Deflection','FontSize',18);
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
   % caxis([0 max(topsedi(:))]);
    box on
    %xlim([0,nx*dx-dx]);
    %ylim([0,ny*dy-dy]);
    
    figure(64485)
    h=surf(X,Y,drain_area);
    set(gca,'fontsize',16)
    title('Drainage area','FontSize',18);
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
   % caxis([0 max(topsedi(:))]);
    box on
    %xlim([0,nx*dx-dx]);
    %ylim([0,ny*dy-dy]);
    
        %}
        
        %{
        vej=long_profile(make_video,do_long,n_pits,topsedi,drain_area,reciever_slope,river,upstream_erosion,sediment_capa,rel_sedi,smooth_saltabr,smooth_diff,smooth_streampower,smooth_erosion,id,reciever,reciever_distance,t,dx,dy,nx,ny,step);
    
        
        S=load('smooth_erosion_before.mat')
        I=find(smooth_erosion==0);
        smooth_erosion(I)=eps;
        I=find(S.smooth_erosion==0);
        S.smooth_erosion(I)=eps;
        
        %overlay_with_drainage_path(vej,X,Y);
        
        h=surf(X,Y,smooth_erosion./S.smooth_erosion,'LineStyle','None');
        shading interp
        
        
        set(gca,'fontsize',16)
        %title(['Smooth Erosion , time: ' num2str(step)],'FontSize',18);
        %text(500,500,'Distance [km]','FontSize',16)
        %text(500,500,'Distance [km]','FontSize',16)
        %xlabel('Distance [m]','FontSize',16)
        %ylabel('Distance [m]','FontSize',16)
        %text(500,500,'Elevation [m]','FontSize',16)
        set(h,'LineStyle','none')
        colorbar;
        set(gca,'fontsize',16,'xticklabel',[],'yticklabel',[])
        axis equal
        %text(600,600,'Elevation [m]','FontSize',16)
        view(2)
        % caxis([0 max(topsedi(:))]);
        caxis([0 2e-3])
        caxis([0 9])
        box on
        xlim([0,nx*dx-dx]);
        ylim([0,ny*dy-dy]);
        %}
        
        
        %{
               figure(2212)
        h=surf(X,Y,drain_area/(dx*dy));
        set(gca,'fontsize',16)
        title('Drain Area','FontSize',18);
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
        % caxis([0 max(topsedi(:))]);
        %caxis([0 2e-3])
        box on
        %xlim([0,nx*dx-dx]);
        %ylim([0,ny*dy-dy]);
        
        
        hFig = figure(5);
        set(gcf, 'Position', [1200, 1100, 1000,700]);
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
        title(['Time: ' num2str(step) ' years'],'FontSize',30);
        %view(2)
        caxis([0 max(topsedi(:))]);
        %caxis([0 5000]);
        %caxis([0 2600]);
        
        
        switch (make_video)
            case ('y')
                frame=getframe(figure(5));
                writeVideo(WriterObj,frame);
        end
        
        
        figure(6)
        h=surf(X,Y,diff);
        set(gca,'fontsize',16)
        title(['Diffusion , time: ' num2str(step)],'FontSize',18);
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
        % caxis([0 max(topsedi(:))]);
        box on
        %xlim([0,nx*dx-dx]);
        %ylim([0,ny*dy-dy]);
        
        
        figure(7)
        h=surf(X,Y,sed_incision);
        set(gca,'fontsize',16)
        title(['Incision , time: ' num2str(step)],'FontSize',18);
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
        % caxis([0 max(topsedi(:))]);
        box on
        %xlim([0,nx*dx-dx]);
        %ylim([0,ny*dy-dy]);
        
         figure(723232)
        h=surf(X,Y,stream_power);
        set(gca,'fontsize',16)
        title('Stream power','FontSize',18);
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
        % caxis([0 max(topsedi(:))]);
        box on
        %xlim([0,nx*dx-dx]);
        %ylim([0,ny*dy-dy]);
        %}
        
        I=find(drain_area<6*dx*dy & id>1110);
        J=find(drain_area>=6*dx*dy & id>1110);
        step_list(counter)=step;
        i_list(counter)=i;
        smooth_erosion_list_small(counter)=mean(smooth_erosion(I));
        smooth_erosion_list_large(counter)=mean(smooth_erosion(J));
        smooth_saltabr_list_small(counter)=mean(smooth_saltabr(I));
        smooth_saltabr_list_large(counter)=mean(smooth_saltabr(J));
        smooth_diff_list_small(counter)=mean(smooth_diff(I));
        smooth_diff_list_large(counter)=mean(smooth_diff(J));
        
        %{
        figure(4545454)
        hold on
        plot(step,av_incision,color)
        title('av incision')
        
        
        figure(2828292)
        hold on
        plot(step,mean(diff(:)),color)
        title('av diffusion')
        
        figure(4547)
        hold on
        plot(step,av_erosion/(dx*dy),color)
        title('av erosion')
        %}
        figure(666)
        hold on
        plot(step,av_height,'*b')
        plot(step,max_height,'*r')
        legend('av height','max height')
        
        %{

         figure(2929)
        plot(reshape(drain_area,[1,numel(drain_area)]),reshape((1-upstream_erosion./sediment_capa),[1,numel(upstream_erosion)]),'*')
 
        figure(2929)
        plot(reshape(upstream_erosion./sediment_capa,[1,numel(upstream_erosion./sediment_capa)]),reshape((upstream_erosion.*(1-upstream_erosion./sediment_capa))./(0.5*sediment_capa.*(1-0.5*sediment_capa./sediment_capa)),[1,numel(upstream_erosion)]),'*')

 figure
 A=reshape(upstream_erosion./sediment_capa,[1,numel(upstream_erosion)]);
 A=sort(A);
 plot(A)
 ylim([0 1])
 
 figure(7)
 hold on
 
 if (jjj==1)
     color='*r';
 elseif (jjj==2)
         color='*b';
 elseif (jjj==3)
         color='*g';
 elseif (jjj==4)
         color='*k';
elseif (jjj==5)
         color='*c';
 else
     color='*r';
 end
     
 plot(step,av_incision,color)
 title('av incision')
 
 
  figure(4547)
 hold on
 plot(step,av_erosion,color)
 title('av incision')
 
 figure(6)
 hold on
 plot(step,av_height,color)
 plot(step,max_height,color)
 legend('av height','max height')
 
 
 figure(8)
 hold on
 sum_total_landslide_erosion=sum(total_landslide_erosion(:))-sum_total_landslide_erosion_old;
 sum_total_landslide_erosion_old=sum(total_landslide_erosion(:));
 subplot(2,1,1)
 title('landslides since last')
 hold on
 plot(step,landslides_since_last,'*r')
 subplot(2,1,2);
 title('Landslide volume since last')
 hold on
 plot(step,sum_total_landslide_erosion,'*r')
 sum_total_landslide_erosion_list(i)=sum_total_landslide_erosion;
 
   step_recorder(i)=step;
   sum_sediment_flux_out(i)=sum(upstream_erosion(1,:));
   sed_flux_out(i,:)=upstream_erosion(1,:);
   
   
    I=find(drain_area>4*200*200 & river==1);
    J=find(drain_area<=4*200*200 & river==1);
    mean_small(i)=mean(erosion(J));
    mean_large(i)=mean(erosion(I));
    step_list(i)=step;
    length_I_list(i)=length(I);
    length_J_list(i)=length(J);
   
    
    
    if (i~=1)
        figure(64373)
        I=find(smooth_erosion_before==0);
        smooth_erosion_before(I)=1e8;
        h=surf(X,Y,smooth_erosion./smooth_erosion_before);
        set(gca,'fontsize',16)
        
        title(['Smooth Erosion change, time: ' num2str(step)],'FontSize',18);

        %title('Erosion change','FontSize',18);
        %text(500,500,'Distance [km]','FontSize',16)
        %text(500,500,'Distance [km]','FontSize',16)
        xlabel('Distance [m]','FontSize',16)
        ylabel('Distance [m]','FontSize',16)
        %text(500,500,'Elevation [m]','FontSize',16)
        set(h,'LineStyle','none')
        colorbar;
        set(gca,'fontsize',16)
        axis equal
        %text(600,600,'Elevation [m]','FontSize',16)
        view(2)
        caxis([0 3]);
        box on
        %xlim([0,nx*dx-dx]);
        %ylim([0,ny*dy-dy]);
    end
    

        %}
        %pause(0.02)
        if (i==frame_mod)
            %tilefigs;
        end
        
        
        
        switch (make_video)
            case ('y')
                frame=getframe(figure(4));
                writeVideo(WriterObj2,frame);
        end 
    end
end

figure(1212123)
hold on
plot(step_list,smooth_erosion_list_small./(dx*dy),'-b','LineWidth',2)
plot(step_list,smooth_erosion_list_large./(dx*dy),'-r','LineWidth',2)
plot(step_list,smooth_saltabr_list_small,'--b','LineWidth',2)
plot(step_list,smooth_saltabr_list_large,'--r','LineWidth',2)
plot(step_list,smooth_diff_list_small,':b','LineWidth',2)
plot(step_list,smooth_diff_list_large,':r','LineWidth',2)

plot([step_list(18-i_start) step_list(18-i_start)],[0 3.5e-3],'--g','LineWidth',2)
plot([step_list(40-i_start) step_list(40-i_start)],[0 3.5e-3],'--k','LineWidth',2)
plot([step_list(115-i_start) step_list(115-i_start)],[0 3.5e-3],'--c','LineWidth',2)
ylim([0 3.5e-3])
xlabel('Time [y]');
ylabel('Erosion rate')
h=legend('Total erosion on hillslopes','Total erosion in trunk rivers','Incision on hillslopes','Incision in trunk rivers','Diffusion on hillslopes','Diffusion in trunk rivers')
h=set(h,'FontSize',12)
box on

switch (make_video)
    case ('y')
        close(WriterObj);
        close(WriterObj2);
        close(WriterObj3);
end

%{
figure(1111)
plot(step_list,mean_small/mean(mean_small(2:end)),'-*')
hold all
plot(step_list,mean_large/mean(mean_large(2:end)),'-*')
title('Erosion in small and large catchments')
legend('Small 100-1','Large 100-1','Small 100-10','Large 100-10','Small 1-100','Large 1-100','Small 1-10','Large 1-10')
figure(121212)
plot(step_list,length_I_list,'-*');
hold all
plot(step_list,length_J_list,'-*');
title('Number of nodes in small and large catchments')
legend('Small 100-1','Large 100-1','Small 100-10','Large 100-10','Small 1-100','Large 1-100','Small 1-10','Large 1-10')

% end

figure(10)
plot(step_recorder,sum_sediment_flux_out,'-')
%hold on
plot([0 max(step_recorder)],[4e-3*dx*dy*nx*ny 4e-3*dx*dy*nx*ny])
figure(11)
plot(step_recorder,sed_flux_out,'-')

%}

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

%%
%{
figure
title('Sediment flux out of system')
I=find(step_recorder>0);
hold all
for i=2:132
    plot(step_recorder(I),sed_flux_out(I,i))
end
%}

