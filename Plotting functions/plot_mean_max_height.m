%function read_output()

%This function plots the evolution of the max and the mean height in the
%model.

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
    folder=sprintf('/onlydown_1MA_new/')
    
    
    
    
    
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
    
    do_long='n'
    make_video='n'
    %fclose(fud);
    smooth_erosion=zeros(ny,nx);
    %nx=0;
    %ny=0;
    
    %for i=1:n_outputs/frame_mod+1
    i=2;
    i_start=i;
    counter=0;
        frame_mod=1;

    while (fud~=-1)
        i=i+frame_mod;
        counter=counter+1;
        %i=18;
        %i=40;
        %i=115;
        
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
        
        figure(666)
        hold on
        plot(step,av_height,'*b')
        plot(step,max_height,'*r')
        legend('av height','max height')
        
    
    end
end
