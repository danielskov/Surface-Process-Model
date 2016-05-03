function  [vej_list_k,vej_list_d]=long_profile(make_video,do_long,n_pits,topsedi,drain_area,reciever_slope,river,upstream_erosion,sediment_capa,rel_sedi,smooth_saltabr,smooth_diff,smooth_streampower,smooth_erosion,id,reciever,reciever_distance,t,dx,dy,nx,ny,step,catchment)

        color='*b';

figure(21474836)
        set(gcf, 'Position', [1200, 100, 1000,700]);
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
                    vej_list_k=[];
                    vej_list_d=[];
                    
                    if (t==1)
                        [k,d] = find(topsedi==max(topsedi(:)));
                        
                        %These next four lines is if we want to find the
                        %next largest peak
                        %catc=catchment(k,d);
                        %I=find(catchment~=catc);
                        %k=find(topsedi==max(topsedi(I)));
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
                    distance(j)=0;
                    sed_incision_(j)=smooth_saltabr(k,d);
                    diff_(j)=smooth_diff(k,d);
                    stream_power_(j)=smooth_streampower(k,d);
                    erosion_(j)=smooth_erosion(k,d)/(dx*dy);
                    vej(j)=id(k,d)+1;
                    vej_list_k(j)=k;
                    vej_list_d(j)=d;
                    
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
                        sed_incision_(j)=smooth_saltabr(r,c);
                        diff_(j)=smooth_diff(r,c);
                        stream_power_(j)=smooth_streampower(r,c);
                        erosion_(j)=smooth_erosion(r,c)/(dx*dy);
                        vej(j)=id(r,c)+1;
                        vej_list_k(j)=r;
                        vej_list_d(j)=c;
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
                    
                    J=find(rel_sedi_>1);
                    rel_sedi_(J)=1;
                    II=find(river_or_not==1);
                    III=find(river_or_not==0);
                    cumsumdistance=cumsum(distance);
                    %cumsumdistance=cumsumdistance(end)-cumsumdistance;

                    %         figure(4)
                    % %        loglog(cumsumdistance,long_profile)
                    %         loglog(drain_area_(II),gradients(II),'r');
                    %         loglog(drain_area_(III),gradients(III),'b');
                    %         xlabel('drain_area');
                    %         ylabel('slope');
                    %         title(['Long profile , time: ' num2str(step)],'FontSize',18);
                    
                    %         figure(28282828)
                    %         plot(cumsumdistance,long_profile)
                    %         xlabel('distance from base')
                    %         ylabel('height')
                    
                    figure(21474836)
                    %set(gcf, 'Position', [1200, 100, 1000,700]);
                    %subplot(8,1,1)
                    %plot([0 1],[0 1]);
                    %plot(cumsumdistance,fqs_,color)
                    %title(['fqs. time: ' num2str(step) 'step:' num2str(i)],'FontSize',18);
                    subplot(7,1,1)
                    plot(cumsumdistance,rel_sedi_,color)
                    title(['rel sedi. time: ' num2str(step) 'step:' num2str(i)],'FontSize',18);
                    subplot(7,1,2)
                    plot(cumsumdistance,sed_incision_,color)
                    title('sed incision')
                    subplot(7,1,3)
                    plot(cumsumdistance,diff_,color)
                    title('diff')
                    subplot(7,1,4)
                    plot(cumsumdistance,stream_power_,color)
                    title('Stream power')
                    subplot(7,1,5)
                    plot(cumsumdistance,erosion_,color)
                    title('Total Erosion')
                    subplot(7,1,6)
                    plot(cumsumdistance,drain_area_,color)
                    title('Drain Area')
                    
                    figure(289)
                    hold on
                    subplot(3,1,1)
                    hold on
                    %plot(cumsumdistance,erosion_,'-g')
                    %plot(cumsumdistance,erosion_,'-k')
                    plot(cumsumdistance,erosion_,'-c')
                    ylim([0 7e-3])
                    legend('Initial steady state','Transient phase','New quasi steady state')
                    title('Total Erosion')
                    subplot(3,1,2)
                    hold on
                    %plot(cumsumdistance,sed_incision_,'-g')
                    %plot(cumsumdistance,sed_incision_,'-k')
                    plot(cumsumdistance,sed_incision_,'-c')
                    ylim([0 7e-3])
                    title('Incision')
                    subplot(3,1,3)
                    hold on
                    %plot(cumsumdistance,diff_,'-g')
                    %plot(cumsumdistance,diff_,'-k')
                    plot(cumsumdistance,diff_,'-c')
                    ylim([0 1.5e-3])
                    title('Diffusion')
                    vej_=zeros(nx,ny);
                    %vej_2=sub2ind(id,vej);
                    [ii,jj]=ind2sub(size(id),vej);
                    %vej_(ii,jj)=1;
                    
                    for iii=1:length(ii)
                        vej_(jj(iii),ii(iii))=1;
                    end
                    figure(828233)
                    subplot(2,1,1)
                    imagesc(vej_)
                    subplot(2,1,2)
                    imagesc(topsedi)
                    
                    clear drain_area_ gradients distance river_or_not
                end
                switch (make_video)
                    case ('y')
                        frame=getframe(figure(21474836));
                        writeVideo(WriterObj3,frame);
                end
                %hold on
                figure(22021345)
                plot(cumsumdistance,long_profile/max(long_profile(:)))
                %plot(cumsumdistance,drain_area_/max(drain_area(:)))
                
        end