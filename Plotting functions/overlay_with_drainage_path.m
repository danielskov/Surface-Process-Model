function overlay_with_drainage_path(vej_list_d,vej_list_k,dx,dy)

figure(523452)
 plot3(dx*vej_list_d-dx,dy*vej_list_k-dy,20*ones(length(vej_list_k)),'r','LineWidth',2)