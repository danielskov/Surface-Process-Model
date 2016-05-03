function large_plot(fId,X,Y,river,step,n_pits,dx,dy,topsedi,landslide_deposition,moved_sediment,sediment_thickness,total_landslide_erosion,reciever_slope,rel_sedi,fluvial_deposition,sediment_capa,fluv,diff,erosion,in_stack,stream_power,nx,ny,sed_incision,bed)



num_plots_x=7;
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
    title(['Fluvial evolution, time: ' num2str(step) ' npits: ' num2str(n_pits) ' n=1'],'FontSize',30);
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
 
    
    %subplot(2,5,2)
    %subplot('Position',[0.23 0.01 0.16 0.45]);
    subplot('Position',[2/num_plots_x+0.03 0/num_plots_y+0.01 1/num_plots_x-0.04 1/num_plots_y-0.05]);
    h=surf(X,Y,total_landslide_erosion);
    %h=surf(X,Y,landslide_erosion);
    set(h,'LineStyle','none')
    colorbar;
    %axis equal
    view(2)
    %caxis([0 max(landslide_erosion(:))+1e-8]);
    caxis([0 max(total_landslide_erosion(:))+1e-8]);
    xlim([0,nx*dx-dx]);
    ylim([0,ny*dy-dy]);
    title('landslide erosion')
    
    
    %subplot(2,5,3)
    %subplot('Position',[0.43 0.01 0.16 0.45]);
    subplot('Position',[3/num_plots_x+0.03 0/num_plots_y+0.01 1/num_plots_x-0.04 1/num_plots_y-0.05]);
    %h=surf(X,Y,abs(reciever_slope));
    h=surf(X,Y,180*atan(reciever_slope)/pi())

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
    caxis([min(diff(:)/(dx*dy))-1e-14 max(diff(:))+1e-8]);
    xlim([0,nx*dx-dx]);
    ylim([0,ny*dy-dy]);
    title('Diff erosion pa')
    

    
    %subplot(2,5,5)
    %subplot('Position',[0.83 0.01 0.16 0.45]);
    subplot('Position',[5/num_plots_x+0.03 0/num_plots_y+0.01 1/num_plots_x-0.04 1/num_plots_y-0.05]);
    h=surf(X,Y,rel_sedi);
    set(h,'LineStyle','none')
    colorbar;
    %axis equal
    view(2)
    caxis([0 1]);
    xlim([0,nx*dx-dx]);
    ylim([0,ny*dy-dy]);
    title('Rel sedi')
    
    

    
    subplot('Position',[6/num_plots_x+0.03 0/num_plots_y+0.01 1/num_plots_x-0.04 1/num_plots_y-0.05]);
    h=surf(X,Y,fluvial_deposition);
    %h=surf(X,Y,sediment_thickness2);
    set(h,'LineStyle','none')
    colorbar;
    %axis equal
    view(2)
    %caxis([0 max(fluvial_deposition(:))]);
    xlim([0,nx*dx-dx]);
    ylim([0,ny*dy-dy]);
    title('fluvial deposition')
    %title('Sediment thickness 2');


    
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
    h=surf(X,Y,erosion/(dx*dy))
    set(h,'LineStyle','none')
    colorbar;
    %axis equal
    view(2)
    caxis([0 max(erosion(:))/(dx*dy)+1e-8]);
    xlim([0,nx*dx-dx]);
    ylim([0,ny*dy-dy]);
    title('Total erosion per year')
    
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
    

    
    %subplot(2,5,8)
    %subplot('Position',[0.43 0.51 0.16 0.45]);
    subplot('Position',[2/num_plots_x+0.03 1/num_plots_y+0.01 1/num_plots_x-0.04 1/num_plots_y-0.05]);
    h=surf(X,Y,stream_power);
    set(h,'LineStyle','none')
    colorbar;
    %axis equal
    view(2)
    caxis([0 max(stream_power(:))]);
    xlim([0,nx*dx-dx]);
    ylim([0,ny*dy-dy]);
    title('Stream power')
    
    %subplot(2,5,9)
    %subplot('Position',[0.63 0.51 0.16 0.45]);
    subplot('Position',[3/num_plots_x+0.03 1/num_plots_y+0.01 1/num_plots_x-0.04 1/num_plots_y-0.05]);
    h=surf(X,Y,fluv-stream_power);
    set(h,'LineStyle','none')
    colorbar;
    %axis equal
    view(2)
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
    subplot('Position',[5/num_plots_x+0.03 1/num_plots_y+0.01 1/num_plots_x-0.04 1/num_plots_y-0.05]);
    h=surf(X,Y,moved_sediment);
    set(h,'LineStyle','none')
    colorbar;
    %axis equal
    view(2)
    caxis([0 max(moved_sediment(:))]);
    xlim([0,nx*dx-dx]);
    ylim([0,ny*dy-dy]);
    title('Moved sediment')
        

    
    subplot('Position',[6/num_plots_x+0.03 1/num_plots_y+0.01 1/num_plots_x-0.04 1/num_plots_y-0.05]);
    h=surf(X,Y,landslide_deposition);
    set(h,'LineStyle','none')
    colorbar;
    %axis equal
    view(2)
    caxis([0 max(landslide_deposition(:))]);
    xlim([0,nx*dx-dx]);
    ylim([0,ny*dy-dy]);
    title('landslide deposition')
    
    pause(0.002)
    