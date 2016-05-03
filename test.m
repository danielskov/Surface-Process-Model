k=0;
for i=1:nx
    for j=1:ny
        if sediment_capa(i,j)>k
            k=sediment_capa(i,j);
            a=i;
            b=j;
            i
            j
            sediment_capa(i,j)
        end
    end
end


k=0;
for i=1:nx
    for j=1:ny
        if sed_incision(i,j)>k
            k=sed_incision(i,j);
            a=i;
            b=j;
            i
            j
            sed_incision(i,j)
        end
    end
end



%{
clear all; close all;

nx=150;
ny=150;

x=linspace(0,(nx-1),nx);
y=linspace(0,(ny-1),ny);


[X,Y]=meshgrid(x,y);

M=zeros(nx,ny);

sigma=23;

for i=1:nx
    for j=1:nx
        %M(i,j)=exp(-((X(i,j)-nx/4)^2)/(2*sigma^2))+exp(-((Y(i,j)-ny/4)^2)/(2*sigma^2))+exp(-((X(i,j)-3*nx/4)^2)/(2*sigma^2));%+exp(-((Y(i,j)-3*ny/4)^2)/(2*sigma^2));
        %M(i,j)=exp(-(sqrt(((X(i,j)-nx/4)^2+(Y(i,j)-ny/4)^2))^2)/(2*sigma^2))+exp(-(sqrt(((X(i,j)-3*nx/4)^2+(Y(i,j)-ny/4)^2))^2)/(2*sigma^2));%
        M(i,j)=exp(-(((X(i,j)-nx/4)^2+(Y(i,j)-ny/4)^2))/(2*sigma^2))+exp(-(((X(i,j)-3*nx/4)^2+(Y(i,j)-ny/4)^2))/(2*sigma^2));%
    end
end

M=M./2+0.5;

surf(X,Y,M);
%}