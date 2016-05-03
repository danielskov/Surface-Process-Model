function [bed_before,smooth_erosion_before,nx,ny,dx,dy,old_step,step,print_modulo,n_outputs,deltat,n_pits,av_height,max_height,av_incision,landslides_since_last,bed,topsedi,id,reciever,drain_area,reciever_distance,erosion,av_erosion,fluv,diff,fluv_over_diff,rel_sedi,sediment_capa,stream_power,channel_width,reciever_bed_height,reciever_reciever_bed_height,upstream_erosion,landslide_erosion,reciever_slope,moved_sediment,landslide_deposition,fluvial_deposition,in_stack,total_landslide_erosion,river,sediment_thickness2,deflection,smooth_erosion,di,catchment,smooth_relsedi,smooth_diff,smooth_saltabr,smooth_streampower,sed_incision,uplift] = read_parameters(fud,bed,smooth_erosion,step)



    if (i~=1)
            %v=v+bplus*frame_mod;

            bed_before=bed;
            smooth_erosion_before=smooth_erosion;
            nx=fread(fud,1,'int64');
            ny=fread(fud,1,'int64');
            dx=fread(fud,1,'double');
            dy=fread(fud,1,'double');
            old_step=step;
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
        landslides_since_last=landslides_since_last/(step-old_step);
        bed = fread(fud,[nx,ny],'double')';
        topsedi=fread(fud,[nx,ny],'double')';
        id = fread(fud,[nx,ny],'int64')';
        reciever = fread(fud,[nx,ny],'int64')';
        drain_area=fread(fud,[nx,ny],'double')';
        reciever_distance=fread(fud,[nx,ny],'double')';
        erosion=fread(fud,[nx,ny],'double')';
        av_erosion=mean(erosion(:));
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
        sediment_thickness2=fread(fud,[nx,ny],'double')';
        deflection=fread(fud,[nx,ny],'double')';
        smooth_erosion=fread(fud,[nx,ny],'double')';
        di=fread(fud,[nx,ny],'int64')';
        catchment=fread(fud,[nx,ny],'int64')';
        smooth_relsedi=fread(fud,[nx,ny],'double')';
        smooth_diff=fread(fud,[nx,ny],'double')';
        smooth_saltabr=fread(fud,[nx,ny],'double')';
        smooth_streampower=fread(fud,[nx,ny],'double')';
        %sed_incision=fluv-stream_power;
        sed_incision=fread(fud,[nx,ny],'double')';
        uplift=fread(fud,[nx,ny],'double')';
        
        fclose(fud);
