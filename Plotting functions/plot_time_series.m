%function read_output()

%This function plots timeseries of erosion, incision and diffusion. In
%addition it plots grey lines at times when longitudional profiles are
%being plotted.

clc
close all;
clear;

models=2

for jjj=1:models
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
    folder=sprintf('/onlydown_1MA_new_moreoutput2/')
    folder=sprintf('/onlyup_1MA_new_moreoutput/')
    
    
    if (jjj==1)
        folder=sprintf('/onlyup_1MA_new_moreoutput/')
    elseif (jjj==2)
        folder=sprintf('/onlydown_1MA_new_moreoutput2/')
    else
        return
    end
    
    
    
    
    
    frame_mod=1;
    
    grey_times=[100;123;124;125;127;130]; %suits onlyup_1MA_new and onlydown_1MA_new
    grey_times=[25;50;80;125;150;200;250;300;350;420;428;435]; %suits onlyup_1MA_new_moreoutput and onlydown_1MA_new_moreoutput
    grey_times=[35;50;80;150;250;350;410;423;428;435]; %suits onlyup_1MA_new_moreoutput and onlydown_1MA_new_moreoutput
    
    
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
    i=16;
    i_start=i;
    counter=0;
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
        
        
        [bed_before,smooth_erosion_before,nx,ny,dx,dy,old_step,step,print_modulo,n_outputs,deltat,n_pits,av_height,max_height,av_incision,landslides_since_last,bed,topsedi,id,reciever,drain_area,reciever_distance,erosion,av_erosion,fluv,diff,fluv_over_diff,rel_sedi,sediment_capa,stream_power,channel_width,reciever_bed_height,reciever_reciever_bed_height,upstream_erosion,landslide_erosion,reciever_slope,moved_sediment,landslide_deposition,fluvial_deposition,in_stack,total_landslide_erosion,river,sediment_thickness2,deflection,smooth_erosion,di,catchment,smooth_relsedi,smooth_diff,smooth_saltabr,smooth_streampower,sed_incision,uplift] = read_parameters(fud,bed,smooth_erosion,step);
        
        
        I=find(drain_area<6*dx*dy & id>1110);
        J=find(drain_area>=6*dx*dy & id>1110);
        step_list(counter)=step;
        i_list(counter)=i;
        smooth_erosion_list_small(counter)=mean(smooth_erosion(I))/uplift(50,50);
        smooth_erosion_list_large(counter)=mean(smooth_erosion(J))/uplift(50,50);
        smooth_saltabr_list_small(counter)=mean(smooth_saltabr(I))/uplift(50,50);
        smooth_saltabr_list_large(counter)=mean(smooth_saltabr(J))/uplift(50,50);
        smooth_diff_list_small(counter)=mean(smooth_diff(I))/uplift(50,50);
        smooth_diff_list_large(counter)=mean(smooth_diff(J))/uplift(50,50);
        
    end
    
    step_list=step_list-step_list(1);
    figure(1212123)
    box on
    subplot(models,1,jjj)
    box on
    hold on
    plot(step_list./1000,smooth_erosion_list_small./(dx*dy),'-b','LineWidth',4)
    plot(step_list./1000,smooth_erosion_list_large./(dx*dy),'-r','LineWidth',4)
    plot(step_list./1000,smooth_saltabr_list_small,'--b','LineWidth',4)
    plot(step_list./1000,smooth_saltabr_list_large,'--r','LineWidth',4)
    plot(step_list./1000,smooth_diff_list_small,':b','LineWidth',4)
    plot(step_list./1000,smooth_diff_list_large,':r','LineWidth',4)
    xlim([0 max(step_list)/1000])
    %plot([step_list(18-i_start) step_list(18-i_start)],[0 3.5e-3],'--g','LineWidth',2)
    %plot([step_list(40-i_start) step_list(40-i_start)],[0 3.5e-3],'--k','LineWidth',2)
    %plot([step_list(115-i_start) step_list(115-i_start)],[0 3.5e-3],'--c','LineWidth',2)
    
    if (jjj==1)
        ylim([0 2])
        set(gca,'ytick', [0 1 2])
    elseif (jjj==2)
        ylim([0 4])
        set(gca,'ytick', [0 1 2 3 4])
    else
        return
    end
    xlim([0 300])
    
    for i=1:length(grey_times)
        grey_times(i);
        plot([step_list(grey_times(i)-i_start)./(1000) step_list(grey_times(i)-i_start)./(1000)],[0 3.5],'--','LineWidth',2,'color',(i-1)/(length(grey_times)+4)*[1,1,1]);
    end
    
    
    %ylim([0 3.5])
    fontsize=36;
    xlabel('Time [ka]','FontSize',fontsize);
    ylabel('Normalized Erosion rate','FontSize',fontsize)
    %h=legend('Total erosion in small catchments','Total erosion in large catchments','Incision in small catchments','Incision in large catchments','Diffusion in small catchments','Diffusion in large catchments')
    h=legend('Total erosion in small catchments','Total erosion in large catchments','Fluvial Incision in small catchments','Fluvial Incision in large catchments','Hillslope erosion in small catchments',' Hillslope erosion in large catchments')
    h=set(h,'FontSize',fontsize)
    box on
    ax = gca
    ax.FontSize=fontsize;
    
    
    
    if (jjj==1)
        title('Change to faster hillslope erosion','FontSize',fontsize)
    elseif (jjj==2)
        title('Change to slower hillslope erosion','FontSize',fontsize)
    else
        return
    end
    
    
    
    
    
    
end
