clear all; clc
%close all;

folder=sprintf('/step6_streampower/');
folder=sprintf('/step1_streampower_u0/');
folder=sprintf('/ks6e-5_landslides/');
folder=sprintf('/ks6e-5_nouplift_50k/');
%folder=sprintf('/streampower_nouplift_50k/');
folder=sprintf('/ks6e-5_nodiff_50k/');
%folder=sprintf('/streampower_diff/');
folder=sprintf('/maxweath_times_1.0/');
folder=sprintf('/nouplift_1.0/')
%folder=sprintf('/nouplift_250k_0.8/')
folder=sprintf('/3_weath1.0/')
%folder=sprintf('/2_streamstart2_wlandslidesandcrit/')
%folder=sprintf('/weathdiff3_1.0/')
folder=sprintf('/4_split0.1_10ka_nouplift0.2/')
folder=sprintf('/3_split0.1_wdepo/')

folder=sprintf('/longhaul3_wfluvialdepo/')
folder=sprintf('/longhaul3_wo_fluvialdepo/')

%nx=70;




b=['./output' folder 'n_landslides'];
fid = fopen([b]);
n_landslides=fread(fid,1,'int64');
%n_landslides=8000;

%folder=sprintf('');
a= ['./output' folder 'landslides'];
fud = fopen([a]);



step=zeros(1,n_landslides);
node=zeros(1,n_landslides);
catchment=zeros(1,n_landslides);
landslide_size=zeros(1,n_landslides);
nodes_in_slide=zeros(1,n_landslides);
topsedi=zeros(1,n_landslides);
distance_to_base=zeros(1,n_landslides);

for i=1:n_landslides
nx=fread(fud,1,'int64');
ny=fread(fud,1,'int64');
dx=fread(fud,1,'double');
dy=fread(fud,1,'double');
step(i)=fread(fud,1,'double');
node(i)=fread(fud,1,'int64')+1;
catchment(i)=fread(fud,1,'int64')+1;
landslide_size(i)=fread(fud,1,'double');
nodes_in_slide(i)=fread(fud,1,'int64');
topsedi(i)=fread(fud,1,'double');
distance_to_base(i)=fread(fud,1,'double');
end

c= ['./output' folder 'fluxout'];
fip = fopen([c]);

n_step=fread(fip,1,'double');
flux_out_modulo=fread(fip,1,'double')


step_fluxout=zeros(1,n_step/flux_out_modulo);
landslide_out=zeros(n_step/flux_out_modulo,nx);
fluvial_out=zeros(n_step/flux_out_modulo,nx);
catchment_landslide_sum=zeros(n_step/flux_out_modulo,nx);
total_landslide_sum=zeros(n_step/flux_out_modulo,1);
catchment_erosion=zeros(n_step/flux_out_modulo,nx);
catchment_sediment=zeros(n_step/flux_out_modulo,nx);
catchment_av_distance=zeros(n_step/flux_out_modulo,nx);
catchment_streampower=zeros(n_step/flux_out_modulo,nx);
catchment_saltabr=zeros(n_step/flux_out_modulo,nx);
catchment_bedrock_landslide_erosion=zeros(n_step/flux_out_modulo,nx);
catchment_av_height=zeros(n_step/flux_out_modulo,nx);
total_erosion=zeros(n_step/flux_out_modulo,1);
total_streampower=zeros(n_step/flux_out_modulo,1);
total_saltabr=zeros(n_step/flux_out_modulo,1);
total_sediment=zeros(n_step/flux_out_modulo,1);


%n_step=42000
for j=1:n_step/flux_out_modulo
    step_fluxout(j)=fread(fip,1,'double');
    landslide_out(j,:)=fread(fip,nx(1),'double');
    fluvial_out(j,:)=fread(fip,nx(1),'double');
    catchment_landslide_sum(j,:)=fread(fip,nx(1),'double');
    total_landslide_sum(j,1)=sum(catchment_landslide_sum(j,:));
    catchment_erosion(j,:)=fread(fip,nx(1),'double');
    catchment_sediment(j,:)=fread(fip,nx(1),'double');
    catchment_av_distance(j,:)=fread(fip,nx(1),'double');
    catchment_streampower(j,:)=fread(fip,nx(1),'double');
    catchment_saltabr(j,:)=fread(fip,nx(1),'double');
    catchment_bedrock_landslide_erosion(j,:)=fread(fip,nx(1),'double');
    catchment_av_height(j,:)=fread(fip,nx(1),'double');
    total_erosion(j,1)=fread(fip,1,'double')/(120*70*200*200*flux_out_modulo);
    total_streampower(j,1)=fread(fip,1,'double');
    total_saltabr(j,1)=fread(fip,1,'double');
    total_sediment(j,1)=fread(fip,1,'double');
end
sed_out=landslide_out+fluvial_out;


figure
plot(step_fluxout',(landslide_out+fluvial_out)')


mode1=mode(catchment);
D=find(catchment==mode1);
F=find(catchment~=mode1);
mode2=mode(catchment(F));
F=find(catchment==mode2);

landslide_size1=landslide_size(D);
step1=step(D);
distance_to_base1=distance_to_base(D);
catchment1=catchment(D);
sed_out1=sed_out(:,mode1);
catchment_landslide_sum1=catchment_landslide_sum(:,mode1);
catchment_erosion1=catchment_erosion(:,mode1);
catchment_sediment1=catchment_sediment(:,mode1);
catchment_av_distance1=catchment_av_distance(:,mode1);
catchment_streampower1=catchment_streampower(:,mode1);
catchment_saltabr1=catchment_saltabr(:,mode1);
catchment_bedrock_landslide_erosion1=catchment_bedrock_landslide_erosion(:,mode1);
catchment_av_height1=catchment_av_height(:,mode1);



landslide_size2=landslide_size(F);
step2=step(F);
distance_to_base2=distance_to_base(F);
catchment2=catchment(F);
sed_out2=sed_out(:,mode2);
catchment_landslide_sum2=catchment_landslide_sum(:,mode2);
catchment_erosion2=catchment_erosion(:,mode2);
catchment_sediment2=catchment_sediment(:,mode2);
catchment_av_distance2=catchment_av_distance(:,mode2);
catchment_streampower2=catchment_streampower(:,mode2);
catchment_saltabr2=catchment_saltabr(:,mode2);
catchment_bedrock_landslide_erosion2=catchment_bedrock_landslide_erosion(:,mode2);
catchment_av_height2=catchment_av_height(:,mode2);


max1=max(landslide_size1(:));
mean1=mean(landslide_size1(:));
median1=median(landslide_size1(:));

max2=max(landslide_size2(:));
mean2=mean(landslide_size2(:));
median2=median(landslide_size2(:));

I1=find(landslide_size1>=mean1*4);
J1=find(landslide_size1<(mean1*4) & landslide_size1>mean1);
H1=find(landslide_size1<=mean1);

I2=find(landslide_size2>=mean2*4);
J2=find(landslide_size2<(mean2*4) & landslide_size2>mean2);
H2=find(landslide_size2<=mean2);

figure
hold on
for i=1:length(step1)
    plot(step1(i),distance_to_base1(i),'o','MarkerSize',18*ceil(landslide_size1(i))/max1);
end
xlabel('time')
ylabel('distance to base')
title('Catchment with most landslides')

figure
hold on
for i=1:length(step2)
    plot(step2(i),distance_to_base2(i),'o','MarkerSize',18*ceil(landslide_size2(i))/max2);
end
xlabel('time')
ylabel('distance to base')
title('Catchment with second most landslides')


figure
hold on
for i=1:length(step1)
    plot(step1(i),landslide_size1(i),'o','MarkerSize',18*ceil(landslide_size1(i))/max1);
end
xlabel('time')
ylabel('Landslide size')
title('Catchment with most landslides')


figure
hold on
for i=1:length(step2)
    plot(step2(i),landslide_size2(i),'o','MarkerSize',18*ceil(landslide_size2(i))/max2);
end
xlabel('time')
ylabel('Catchment')
title('Catchment with second most landslides')

figure
hold on
plot3(step1(I1),distance_to_base1(I1),landslide_size1(I1),'*','MarkerSize',20)
plot3(step1(J1),distance_to_base1(J1),landslide_size1(J1),'*','MarkerSize', 10)
plot3(step1(H1),distance_to_base1(H1),landslide_size1(H1),'*','MarkerSize', 4)
view(2)
xlabel('time')
ylabel('distance to base')
zlabel('size')
title('Catchment with most landslides')


figure
hold on
plot3(step2(I2),distance_to_base2(I2),landslide_size2(I2),'*','MarkerSize',20)
plot3(step2(J2),distance_to_base2(J2),landslide_size2(J2),'*','MarkerSize', 10)
plot3(step2(H2),distance_to_base2(H2),landslide_size2(H2),'*','MarkerSize', 4)
view(2)
xlabel('time')
ylabel('distance to base')
zlabel('size')
title('Catchment with second most landslides')

figure
hold on
plot3(step1(I1),catchment1(I1),landslide_size1(I1),'*','MarkerSize', 20)
plot3(step1(J1),catchment1(J1),landslide_size1(J1),'*','MarkerSize', 10)
plot3(step1(H1),catchment1(H1),landslide_size1(H1),'*','MarkerSize', 4)
view(2)
xlabel('time')
ylabel('catchment')
zlabel('size')
title('Catchment with most landslides')

windowsize1=5;
windowsize2=55;
b1 = (1/windowsize1)*ones(1,windowsize1);
b2 = (1/windowsize2)*ones(1,windowsize2);

figure
plot(step_fluxout,sed_out1)
hold on
plot(step_fluxout,smooth(sed_out1))
ylabel('flux out')
title('Catchment with most landslides')

figure
plot(step_fluxout,catchment_landslide_sum1)
hold on
plot(step_fluxout,smooth(catchment_landslide_sum1))
ylabel('Total landslide in catchment')
title('Catchment with most landslides')

figure
plot(step_fluxout,catchment_erosion1)
hold on
plot(step_fluxout,smooth(catchment_erosion1))
ylabel('Total erosion in catchment')
title('Catchment with most landslides')

figure
plot(step_fluxout,catchment_sediment1)
hold on
plot(step_fluxout,smooth(catchment_sediment1))
ylabel('Total sediment in catchment')
title('Catchment with most landslides')

figure
plot(step_fluxout,catchment_av_distance1)
hold on
plot(step_fluxout,smooth(catchment_av_distance1,55))
ylabel('Average distance to landslide in catchment')
title('Catchment with most landslides')

figure
title('most landslides')
subplot(9,1,1)
%plot(step_fluxout,smooth(sed_out1)/max(smooth(sed_out1)))
plot(step_fluxout,smooth(sed_out1))
title('sed out')
hold on
subplot(9,1,2)
%plot(step_fluxout,smooth(catchment_landslide_sum1,55)/max(smooth(catchment_landslide_sum1,55)))
plot(step_fluxout,smooth(catchment_landslide_sum1,55))
title('landslide sum')
subplot(9,1,3)
%plot(step_fluxout,smooth(catchment_erosion1)/max(smooth(catchment_erosion1)));
plot(step_fluxout,smooth(catchment_erosion1));
title('catchment erosion')
subplot(9,1,4)
%plot(step_fluxout,smooth(catchment_sediment1)/max(smooth(catchment_sediment1)));
plot(step_fluxout,smooth(catchment_sediment1,55));
title('catchment sediment')
subplot(9,1,5)
%plot(step_fluxout,smooth(catchment_av_distance1,55)/max(smooth(catchment_av_distance1,55)))
plot(step_fluxout,smooth(catchment_av_distance1,55))
title('av distance')
subplot(9,1,6)
%plot(step_fluxout,smooth(catchment_av_distance1,55)/max(smooth(catchment_av_distance1,55)))
plot(step_fluxout,smooth(catchment_streampower1,55))
title('streampower incision')
subplot(9,1,7)
%plot(step_fluxout,smooth(catchment_av_distance1,55)/max(smooth(catchment_av_distance1,55)))
plot(step_fluxout,smooth(catchment_saltabr1,55))
title('saltation abrasion incision')
subplot(9,1,8)
%plot(step_fluxout,smooth(catchment_av_distance1,55)/max(smooth(catchment_av_distance1,55)))
plot(step_fluxout,smooth(catchment_bedrock_landslide_erosion1,55))
title('Landslide bedrock erosion')
subplot(9,1,9)
%plot(step_fluxout,smooth(catchment_av_distance1,55)/max(smooth(catchment_av_distance1,55)))
plot(step_fluxout,smooth(catchment_av_height1))
title('Catchment av height')



figure
hold on
plot3(step2(I2),catchment2(I2),landslide_size2(I2),'*','MarkerSize', 20)
plot3(step2(J2),catchment2(J2),landslide_size2(J2),'*','MarkerSize', 10)
plot3(step2(H2),catchment2(H2),landslide_size2(H2),'*','MarkerSize', 4)
view(2)
xlabel('time')
ylabel('catchment')
zlabel('size')
title('Catchment with second most landslides')

figure
plot(step_fluxout,sed_out2)
hold on
plot(step_fluxout,smooth(sed_out2))
ylabel('flux out')
title('Catchment with second most landslides')

figure
plot(step_fluxout,catchment_landslide_sum2)
hold on
plot(step_fluxout,smooth(catchment_landslide_sum2))
ylabel('Total landslide in catchment')
title('Catchment with second most landslides')


figure
plot(step_fluxout,catchment_erosion2)
hold on
plot(step_fluxout,smooth(catchment_erosion2))
ylabel('Total erosion in catchment')
title('Catchment with second most landslides')

figure
plot(step_fluxout,catchment_sediment2)
hold on
plot(step_fluxout,smooth(catchment_sediment2))
ylabel('Total sediment in catchment')
title('Catchment with second most landslides')

figure
plot(step_fluxout,catchment_av_distance2)
hold on
plot(step_fluxout,smooth(catchment_av_distance2))
ylabel('Average distance to landslide in catchment')
title('Catchment with second most landslides')


figure
title('second most landslides')
subplot(9,1,1)
%plot(step_fluxout,smooth(sed_out2)/max(smooth(sed_out2)))
plot(step_fluxout,smooth(sed_out2))
title('sed out')
hold on
subplot(9,1,2)
%plot(step_fluxout,smooth(catchment_landslide_sum2,55)/max(smooth(catchment_landslide_sum2,55)))
plot(step_fluxout,smooth(catchment_landslide_sum2,55))
title('landslide sum')
subplot(9,1,3)
%plot(step_fluxout,smooth(catchment_erosion2)/max(smooth(catchment_erosion2)));
plot(step_fluxout,smooth(catchment_erosion2));
title('catchment erosion')
subplot(9,1,4)
%plot(step_fluxout,smooth(catchment_sediment2)/max(smooth(catchment_sediment2)));
plot(step_fluxout,smooth(catchment_sediment2));
title('catchment sediment')
subplot(9,1,5)
plot(step_fluxout,smooth(catchment_av_distance2,55))
title('av distance')
subplot(9,1,6)
plot(step_fluxout,smooth(catchment_streampower2,55))
title('streampower incision')
subplot(9,1,7)
plot(step_fluxout,smooth(catchment_saltabr2))
title('saltation abrasion incision')
subplot(9,1,8)
plot(step_fluxout,smooth(catchment_bedrock_landslide_erosion2,55))
title('Landslide bedrock erosion')
subplot(9,1,9)
plot(step_fluxout,smooth(catchment_av_height2))
title('Catchment av height')

figure(200)
plot(step_fluxout,smooth(total_erosion/max(total_erosion)));
hold on
plot(step_fluxout,1+smooth(total_saltabr/max(total_saltabr)));
plot(step_fluxout,2+smooth(total_sediment/max(total_sediment)));
plot(step_fluxout,3+smooth(total_landslide_sum/max(total_landslide_sum)));
legend('erosion','saltabr','sediment','landslide sum')
%close all



figure(300)
hold all
%subplot(4,1,1)
n_smooth=155;

b = (1/n_smooth)*ones(1,n_smooth);

a=smooth(total_erosion,n_smooth);
a=filter(b,1,total_erosion);

%plot(step_fluxout(n_smooth:end-n_smooth),a(n_smooth:end-n_smooth)/max(a(n_smooth:end-n_smooth)));
%plot(step_fluxout(0.3*length(step_fluxout):end-n_smooth)./1e6,a(0.3*length(step_fluxout):end-n_smooth)./1e6);
%plot(step_fluxout(n_smooth:end-n_smooth)./1e6,a(n_smooth:end-n_smooth)./1e6);
plot(step_fluxout(n_smooth:end-n_smooth)./1e6,a(n_smooth:end-n_smooth)*1000);


xlabel('Time [Ma]','FontSize',24)
ylabel('Mean Incision Rate [mm/a]','FontSize',24)
%text('Max Weathering Rates ')
legend('12','18','24','30')
set(gca,'FontSize',24)
%ylim([0 0.2])

%hold on
%plot([0.3*max(step_fluxout)/1e6 0.3*max(step_fluxout)/1e6],[0 max(a(n_smooth:end-n_smooth))],'r--','LineWidth',4)
%set(gca,'FontSize',16)
%ylabel('Normalized Fluvial Erosion')
%title('Saltation abrasion model','FontSize',16)

figure(301)
%subplot(4,1,2)
hold all
n_smooth=155;
a=smooth(total_landslide_sum,n_smooth);
a=filter(b,1,total_landslide_sum);


plot(step_fluxout(n_smooth:end-n_smooth),a(n_smooth:end-n_smooth)/max(a(n_smooth:end-n_smooth)),'k');


hold on
plot([0.3*max(step_fluxout) 0.3*max(step_fluxout)],[0 1],'r--','LineWidth',4)
%xlabel('Time [a]','FontSize',16);
set(gca,'FontSize',16)
%ylabel('Normalized Landsliding')
%title('Saltation abrasion model','FontSize',16)
%legend('Fluvial Erosion','Landslide Erosion')
set(gca,'FontSize',16)


figure
B=sort(landslide_size1,'descend');
C=cumsum(B);
plot(C);
title('Catchment with most landslides')


figure
B=sort(landslide_size2,'descend');
C=cumsum(B);
plot(C);
title('Catchment with second most landslides')

fft1=fft(catchment_landslide_sum1);
fft2=fft(catchment_landslide_sum2);
figure
plot(abs(fft1))
figure
plot(abs(fft2))


tilefigs