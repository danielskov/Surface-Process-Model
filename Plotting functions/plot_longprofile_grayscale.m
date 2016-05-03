%function read_output()

%This function plots longitudional profiles of different parameters, often
%erosion and incision. All erosionrates are normalized by the uplift rate.

clc
close all;
clear;

clear step_list;
clear mean_small;
clear mean_large;
clear length_I_list;
clear length_J_list;


models=2;

for iii=1:models
    
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
    folder=sprintf('/onlydown_1MA_new/')
    %folder=sprintf('/onlyup_1MA_new/')
    %folder=sprintf('/test2/')
    %folder=sprintf('/difftest/')
    
    
    if (iii==1)
        folder=sprintf('/onlyup_1MA_new_moreoutput/')
    elseif (iii==2)
        folder=sprintf('/onlydown_1MA_new_moreoutput2/')
    else
        return
    end
    
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
    smooth_erosion=zeros(ny,nx);
    %nx=0;
    %ny=0;
    grey_times=[100;123;124;125;127;130]; %suits onlyup_1MA_new and onlydown_1MA_new
    grey_times=[40;60;100;120;130;140;150]; %suits test
    grey_times=[25;50;80;125;150;200;250;300;350;400;420;450]; %suits onlyup_1MA_new_moreoutput and onlydown_1MA_new_moreoutput
    grey_times=[35;50;80;150;250;350;410;423;428;435]; %suits onlyup_1MA_new_moreoutput and onlydown_1MA_new_moreoutput
    grey_times=[35;70;120;240;350;410;423;435]; %suits onlyup_1MA_new_moreoutput and onlydown_1MA_new_moreoutput
    %grey_times=[354;355;364;374;384;394;404]; %suits onlyup_1MA_new_moreoutput. Bruges til at vise knickpointet som propagerer opad. Initierer mellem 354 og 355
    grey_times=[35;45;55;65;70;120;240;350;410;423;435]; %suits onlyup_1MA_new_moreoutput and onlydown_1MA_new_moreoutput
    grey_times=[35;50;80;150;250;350;410;423;428;435]; %suits onlyup_1MA_new_moreoutput and onlydown_1MA_new_moreoutput

    %grey_times=40:10:440;
    
    %for i=1:n_outputs/frame_mod+1
    i=2;
    i_start=i;
    counter=0;
    for iiiii=1:length(grey_times)
        i=grey_times(iiiii);
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
        
        
        color='*b';
        
        switch(do_long)
            case 'y'
                if n_pits==0
                    long_profile=[];
                    distance=[];
                    drain_area_=[];
                    gradients=[];
                    fqs_=[];
                    rel_sedi_=[];
                    sed_incision_=[];
                    diff_=[];
                    stream_power_=[];
                    erosion_=[];
                    vej=[];
                    smooth_rel_sedi_=[];
                    sediment_thick_=[];
                    
                    if (t==1)
                        [k,d] = find(topsedi==max(topsedi(:)));
                        catc=catchment(k,d);
                        %I=find(catchment~=catc);
                        %k=find(topsedi==max(topsedi(I)))
                        %[k,d]=ind2sub(size(topsedi),k);
                        %catc2=catchment(k,d);
                        
                        %J=find(catchment~=catc & catchment~=catc2);
                        %k=find(topsedi==max(topsedi(J)));
                        %[k,d]=ind2sub(size(topsedi),k);
                        %catc3=catchment(k,d);
                        
                        if (length(k)>1)
                            k=k(1);
                            d=d(1);
                        end
                        t=2;
                    end
                    H=gcf;
                    %Tributaries(H,catchment,k,d,drain_area,dx,dy,topsedi,reciever_distance,id,reciever,nx,ny);
                    
                    j=1;
                    long_profile(j)=topsedi(k,d);
                    drain_area_(j)=drain_area(k,d);
                    gradients(j)=reciever_slope(k,d);
                    river_or_not(j)=river(k,d);
                    fqs_(j)=upstream_erosion(k,d)*(1-upstream_erosion(k,d)/sediment_capa(k,d));
                    %rel_sedi_(j)=upstream_erosion(k,d)/sediment_capa(k,d);
                    rel_sedi_(j)=rel_sedi(k,d);
                    smooth_rel_sedi_(j)=smooth_relsedi(k,d);
                    distance(j)=0;
                    sed_incision_(j)=smooth_saltabr(k,d)/uplift(k,d);
                    diff_(j)=smooth_diff(k,d)/uplift(k,d);
                    stream_power_(j)=smooth_streampower(k,d)/uplift(k,d);
                    erosion_(j)=smooth_erosion(k,d)/(dx*dy*uplift(k,d));
                    vej(j)=id(k,d)+1;
                    sediment_thick_(j)=sediment_thickness2(k,d);
                    
                    [r,c] = find(id==reciever(k,d));
                    while (topsedi(r,c)>=0)
                        j=j+1;
                        distance(j)=reciever_distance(r,c);
                        drain_area_(j)=drain_area(r,c);
                        gradients(j)=reciever_slope(r,c);
                        river_or_not(j)=river(k,d);
                        fqs_(j)=upstream_erosion(r,c)*(1-upstream_erosion(r,c)/sediment_capa(r,c));
                        %rel_sedi_(j)=upstream_erosion(r,c)/sediment_capa(r,c);
                        rel_sedi_(j)=rel_sedi(r,c);
                        smooth_rel_sedi_(j)=smooth_relsedi(r,c);
                        sed_incision_(j)=smooth_saltabr(r,c)/uplift(r,c);
                        diff_(j)=smooth_diff(r,c)/uplift(r,c);
                        stream_power_(j)=smooth_streampower(r,c)/uplift(r,c);
                        erosion_(j)=smooth_erosion(r,c)/(dx*dy*uplift(r,c));
                        vej(j)=id(r,c)+1;
                        sediment_thick_(j)=sediment_thickness2(r,c);
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
                    
                    cumsumdistance=cumsum(distance);
                    figure(2)
                    box on
                    
                    subplot(models,1,iii)
                    hold on
                    plot(cumsumdistance./(1000),erosion_,'-','color',(iiiii-1)/(length(grey_times)+4)*[1,1,1],'LineWidth',4)
                    
                    
                                      
                    if (iii==1)
                        ylim([0 3])
                        set(gca,'ytick', [0 1 2 3])
                    elseif (iii==2)
                        ylim([0 8])
                        set(gca,'ytick', [0 2 4 6 8])
                    else
                        return
                    end
                    %legend('Initial steady state','Transient phase','New quasi steady state')
                    box on
                    
                    fontsize=36;
                    if (iii==1)
                        title('Change to faster hillslope erosion','FontSize',fontsize)
                    elseif (iii==2)
                        title('Change to slower hillslope erosion','FontSize',fontsize)
                    else
                        return
                    end
                    
                    
                    ylabel('Normalized erosion','FontSize',fontsize)
                    xlabel('Distance from divide [km]','FontSize',fontsize)
                    ax = gca
                    ax.FontSize=fontsize;
                    
                    
                    figure(289*iii)
                    box on
                    
                    hold on
                    subplot(4,1,1)
                    hold on
                    
                    plot(cumsumdistance,erosion_,'-','color',(iiiii-1)/length(grey_times)*[1,1,1],'LineWidth',2)
                    plot(cumsumdistance,diff_,'color',(iiiii-1)/length(grey_times)*[1,1,1],'LineWidth',2)
                    ylim([0 8])
                    ylim([0 3])
                    %legend('Initial steady state','Transient phase','New quasi steady state')
                    box on
                    title('Total Erosion')
                    subplot(4,1,2)
                    hold on
                    %plot(cumsumdistance,sed_incision_,'-g')
                    %plot(cumsumdistance,sed_incision_,'-k')
                    plot(cumsumdistance,sediment_thick_,'color',(iiiii-1)/(length(grey_times)+4)*[1,1,1],'LineWidth',2)
                    %plot(cumsumdistance,diff_,'color',(iiiii-1)/(length(grey_times)+4)*[1,1,1],'LineWidth',2)
                    
                    %plot(cumsumdistance,smooth_rel_sedi_,'color',(iiiii-1)/(length(grey_times)+4)*[1,1,1],'LineWidth',2)
                    %ylim([0 3])
                    box on
                    title('Incision')
                    subplot(4,1,3)
                    hold on
                    %plot(cumsumdistance,diff_,'-g')
                    %plot(cumsumdistance,diff_,'-k')
                    %plot(cumsumdistance,diff_,'color',(iiiii-1)/(length(grey_times)+4)*[1,1,1],'LineWidth',2)
                    plot(cumsumdistance,rel_sedi_,'color',(iiiii-1)/(length(grey_times)+4)*[1,1,1],'LineWidth',2)
                    %plot(cumsumdistance,drain_area_,'color',(iiiii-1)/(length(grey_times)+4)*[1,1,1],'LineWidth',2)
                    ylim([0 1.5])
                    box on
                    %title('Diffusion')
                    subplot(4,1,4)
                    hold on
                    %plot(cumsumdistance,diff_,'-g')
                    %plot(cumsumdistance,diff_,'-k')
                    %plot(cumsumdistance,diff_,'color',(iiiii-1)/(length(grey_times)+4)*[1,1,1],'LineWidth',2)
                    %plot(cumsumdistance,gradients,'color',(iiiii-1)/(length(grey_times)+4)*[1,1,1],'LineWidth',2)
                    %plot(cumsumdistance,drain_area_,'color',(iiiii-1)/(length(grey_times)+4)*[1,1,1],'LineWidth',2)
                    %plot(cumsumdistance,gradients);
                    %loglog(cumsumdistance,long_profile);
                    %box on
                    %ylim([0 1.5])
                    %title('Diffusion')
                    
                    %clear drain_area_ gradients distance river_or_not
                end
                
                %figure
                %surf(X,Y,reciever_slope)
                %colorbar
                %view(2)
                
        end
        
    end
end
