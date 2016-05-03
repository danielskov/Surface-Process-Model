%function makeinput()
clear;
close all;

nx=71; ny=71; 
dx=200;
dy=200;
x=linspace(0,(nx-1),nx);
y=linspace(0,(ny-1),ny);
my=0.3;
L=50;
feed=1000;
feed2=400;
new_start='yes'  %This parameter must be assigned to either 'no', to load an old file, or 'yes', to generate a new starting model.

switch (new_start)
    case 'no'
b=0;
starting_model_name='newstart'
starting_model_name='afternewstart'
starting_model_name='notimechange_output'
%starting_model_name='streampower_nosedi'

a= ['./starting_models/' starting_model_name];
fud = fopen([a]);  
    nx=fread(fud,1,'int64');
    ny=fread(fud,1,'int64');
    dx=fread(fud,1,'double');
    dy=fread(fud,1,'double');
    step=fread(fud,1,'double');
    print_modulo=fread(fud,1,'double');
    number_of_outputs=fread(fud,1,'double');
    deltat=fread(fud,1,'double');
    pits=fread(fud,1,'double');
    av_height=fread(fud,1,'int64');
    max_height=fread(fud,1,'int64');
    av_incision=fread(fud,1,'double')
    av_incision=fread(fud,1,'int64')


M = fread(fud,[nx,ny],'double')+1e-5; %The small factor is added to make sure that only the right nodes are baselevel nodes
sed = fread(fud,[nx,ny],'double')+1e-5; %The small factor is added to make sure that only the right nodes are baselevel nodes
%sed=M; %This line should be included if we wish to set the initial
%sediment thickenss to zero.
M=M';
sed=sed';
%sed=sed+M;

    case 'yes'
sed = karman2d(x(:),y(:),my,L,feed2);
sed = sed-min(sed(:))+0.001;
amplitude=0*1;
sed=sed.*(amplitude/max(sed(:)));

%M = 2*rand(nx,ny)+0.0001;
M = karman2d(x(:),y(:),my,L,feed);
M = M-min(M(:))+0.001;
amplitude=0.00200;
M=M.*(amplitude/max(M(:)));%+20;
imagesc(M)

for i=1:ny
 %   M(i,:)=M(i,:)*(10*y(i)/nx+0.01)+100*y(i)/nx;
    M(i,:)=10*y(i)/max(y(:))+2*rand(nx,1)+0.1;
    %M(i,:)=10*max(y(i))*y(i)/max(y(:));
    %M(i,:)=M(i,:)+M(i,:)*(((ny/2)-abs(y(i)-ny/2))/nx+0.01)+10e3*((ny/2)-abs(y(i)-ny/2))/nx;
    %sed(i,:)=M(i,:);
    %M(i,:)=1e-8;
end
%M=M';
%sed=sed';
sed=sed+M;
end

%M(1,1)=0;
M(1,1:end)=0;
%M(end,1:end)=0;
%M(1:end,1)=0;
%M(1:end,end)=0;

%sed(1,1)=0;
sed(1,1:end)=0;
%sed(end,1:end)=0;
%sed(1:end,1)=0;
%sed(1:end,end)=0;
I=find(M<0)
M(I)=1e-8;



%{
M(floor(nx/2),floor(ny/2))=0;
M(floor(nx/3),floor(ny/2))=0;
M(floor(2*nx/3),floor(ny/2))=0;
M(floor(nx/2),floor(ny/3))=0;
M(floor(nx/2),floor(2*ny/3))=0;
%}
step=0;
fid = fopen('./meshdata.input','wb');
fwrite(fid,nx,'int64');
fwrite(fid,ny,'int64');
fwrite(fid,dx,'double');
fwrite(fid,dy,'double');
fwrite(fid,step,'double');
for i=1:ny,
    i
  for j=1:nx,
    fwrite(fid,M(i,j),'double');
    fwrite(fid,sed(i,j),'double');
  end;
end;
fclose(fid);

imagesc(M)
colorbar;

figure
imagesc(sed)
colorbar;

figure
nc=200;
points_per_edge=20;
domain_distance=20000;
X=domain_distance*(rand(nc,1));
X= [zeros(points_per_edge,1) ; domain_distance*rand(points_per_edge,1) ; domain_distance*ones(points_per_edge,1) ; domain_distance*rand(points_per_edge,1) ; X];
Y=domain_distance*(rand(nc,1));
Y=[domain_distance*rand(points_per_edge,1) ; domain_distance*ones(points_per_edge,1); domain_distance*rand(points_per_edge,1); zeros(points_per_edge,1); Y];
Z=X+20*rand(nc+4*points_per_edge,1);
tri=delaunay(X,Y);
trisurf(tri,X,Y,Z)
