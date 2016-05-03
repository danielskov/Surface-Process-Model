%function read_output()

%This function plots the normalized smooth erosion, overlayed with the fluvial
%network. The mat file smooth_erosion_before.mat should be present in the
%folder. This mat should contain the 
%The plots can be used to show the erosional state before an
%pertubation. The drainage path shown in longitudional profiles will be
%overlaid the surf of the erosion. Drainage paths of other large rivers are
%overlaid in black colors.

clc
%close all;
clear;

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
    folder=sprintf('/test/')
folder=sprintf('/onlyup_1MA_new_moreoutput/')

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
    
    smooth_erosion=zeros(ny,nx);
    i=2;
    i_start=i;
    counter=0;
    %while (fud~=-1)
        i=i+frame_mod;
        counter=counter+1;
        i=18;
        
        v=i-1;
        b=sprintf('%014.2f',v);
        %a= ['./output/output' num2str(b)];
        a= ['../output' folder '/output' num2str(b)];
        
        %a= ['./output/output' num2str(b) '.dat'];
        fud = fopen([a]);
        
        
        [bed_before,smooth_erosion_before,nx,ny,dx,dy,old_step,step,print_modulo,n_outputs,deltat,n_pits,av_height,max_height,av_incision,landslides_since_last,bed,topsedi,id,reciever,drain_area,reciever_distance,erosion,av_erosion,fluv,diff,fluv_over_diff,rel_sedi,sediment_capa,stream_power,channel_width,reciever_bed_height,reciever_reciever_bed_height,upstream_erosion,landslide_erosion,reciever_slope,moved_sediment,landslide_deposition,fluvial_deposition,in_stack,total_landslide_erosion,river,sediment_thickness2,deflection,smooth_erosion,di,catchment,smooth_relsedi,smooth_diff,smooth_saltabr,smooth_streampower,sed_incision,uplift] = read_parameters(fud,bed,smooth_erosion,step);
        
        [vej_list_k,vej_list_d]=long_profile('n','y',n_pits,topsedi,drain_area,reciever_slope,river,upstream_erosion,sediment_capa,rel_sedi,smooth_saltabr,smooth_diff,smooth_streampower,smooth_erosion,id,reciever,reciever_distance,t,dx,dy,nx,ny,step,catchment);
        
        
        %S=load('smooth_erosion_before.mat')
        S=load('uplift.mat')
        I=find(smooth_erosion==0);
        smooth_erosion(I)=eps;
        I=find(S.uplift==0);
        S.uplift(I)=eps;
        
        overlay_other_rivers(catchment,drain_area,dx,dy,topsedi,reciever_distance,id,reciever,nx,ny,X,Y)
        
%        plot3(dx*vej_list_d-dx,dy*vej_list_k-dy,ones(length(vej_list_k)),'r','LineWidth',2)

        overlay_with_drainage_path(vej_list_d,vej_list_k,dx,dy);
        
        fId=figure(523452)
        set(fId,'Color',[224/255 242/255 245/255]);

        %h=surf(X,Y,drain_area./1e8,'LineStyle','None');
        %shading interp
        %return
        
        h=surf(X,Y,smooth_erosion./(dx*dy*S.uplift),'LineStyle','None');
        %shading interp
        
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
        caxis([0 7])
        box on
        %set(gca,'color','none')
        xlim([0,nx*dx-dx]);
        ylim([0,ny*dy-dy]);
        
        
        return
  