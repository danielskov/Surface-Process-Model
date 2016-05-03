function overlay_other_rivers(catchment,drain_area,dx,dy,topsedi,reciever_distance,id,reciever,nx,ny,X,Y)

%[num idx] = max(drain_area(:));
%[x y] = ind2sub(size(drain_area),idx);

%close all
%I=find(catchment==catchment(k,d) & drain_area==(6*dx*dy));
hold on

for i=1:nx*ny
%for i=1:length(I)
    [k,d] = ind2sub(size(drain_area),i);
    if (drain_area(k,d)>5*dx*dy & drain_area(k,d)<16*dx*dy)
    %if (drain_area(k,d)==6*dx*dy)
    vej_=[];
    vej_new=[];
    X_new=[];
    Y_new=[];
    vej=[];
    vej_list_k=[];
    vej_list_d=[];
    %[k,d] = ind2sub(size(drain_area),I(i));
    
    j=1;
    vej(j)=id(k,d)+1;
    vej_list_k(j)=k;
    vej_list_d(j)=d;
    [r,c] = find(id==reciever(k,d));
    j=2;
    vej(j)=id(r,c)+1;
 vej_list_k(j)=r;
    vej_list_d(j)=c;
    
    %             disp('k,d')
%         [k,d]
%         disp('r,c')
%         [r,c]
    while (topsedi(r,c)>=0)
        j=j+1;
        n=r; u=c;
        [r,c]=find(id==reciever(r,c));

        
%         if (j==2)
%                        disp('n,u')
%         [n,u]
%         disp('r,c')
%         [r,c]
%             
%         end
        
        vej(j)=id(r,c)+1;
    vej_list_k(j)=r;
    vej_list_d(j)=c;
    
        
        if n==r && u==c break
        end
        if j>(nx*ny)
            disp('fejl')
            return;
        end
    end
    
    
    
    vej_=zeros(nx,ny);
    %vej_2=sub2ind(id,vej);
    [ii,jj]=ind2sub(size(id),vej);
    %vej_(ii,jj)=1;
    
    for iii=1:length(ii)
        vej_(jj(iii),ii(iii))=1;
    end
    
    I=find(vej_'==1); %This is the path of the drainage that I show in the long profile
        [hj,jh]=ind2sub(size(vej_),I);
        
        for ik=1:length(hj)
                X_new(ik)=X(jh(ik),hj(ik));
        end
        
        
        for ik=1:length(hj)
                Y_new(ik)=X(hj(ik),jh(ik));
        end
        
        for ik=1:length(hj)
                vej_new(ik)=vej_(jh(ik),hj(ik));
        end
        
       
%         figure(523452)
%               hold on
%         plot3(X_new,Y_new,1e3*vej_new,'k','LineWidth',2)
        
                figure(523452)

        hold on
        %plot3(X(vej_list_k,vej_list_d),X(vej_list_d,vej_list_k),ones(length(vej_list_k)),'k','LineWidth',2)
        %plot3(dx*vej_list_k'-dx,dy*vej_list_d'-dy,ones(length(vej_list_k)),'k','LineWidth',2)
        plot3(dx*vej_list_d-dx,dy*vej_list_k-dy,19*ones(length(vej_list_k)),'k','LineWidth',2)

        %view(2)
        
%         disp('k')
%         vej_list_k
%         disp('d')
%         vej_list_d
%         
        %pause(2)
    end  
end


