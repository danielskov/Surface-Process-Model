function Tributaries(H,catchment,k,d,drain_area,dx,dy,topsedi,reciever_distance,id,reciever,nx,ny)

%[num idx] = max(drain_area(:));
%[x y] = ind2sub(size(drain_area),idx);

%close all
I=find(catchment==catchment(k,d) & drain_area==(6*dx*dy));
hold on
length(I);
for i=1:length(I)
    long_profile=[]; 
    distance=[];
    
    [k,d] = ind2sub(size(drain_area),I(i));
    
    j=1;
    long_profile(j)=topsedi(k,d);
    distance(j)=reciever_distance(k,d);
    
    [r,c] = find(id==reciever(k,d));
    while (topsedi(r,c)>=0)
        j=j+1;
        distance(j)=reciever_distance(r,c);
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
    cumsumdistance=cumsumdistance(end)-cumsumdistance;
    
    figure(H)
    subplot(7,1,7)
    hold on
    plot(cumsumdistance,long_profile,'-')
    
end


