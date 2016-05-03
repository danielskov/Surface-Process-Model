clear; clc
close all;

folder=sprintf('/weathout_test/');


n_models=14;
n_splits=7;


mean_weath_list0=zeros(1,n_models);
mean_erosion_list0=zeros(1,n_models);
mean_weath_list01=zeros(1,n_models);
mean_erosion_list01=zeros(1,n_models);
mean_weath_list03=zeros(1,n_models);
mean_erosion_list03=zeros(1,n_models);
mean_weath_list05=zeros(1,n_models);
mean_erosion_list05=zeros(1,n_models);
mean_weath_list07=zeros(1,n_models);
mean_erosion_list07=zeros(1,n_models);
mean_weath_list09=zeros(1,n_models);
mean_erosion_list09=zeros(1,n_models);
mean_weath_list10=zeros(1,n_models);
mean_erosion_list10=zeros(1,n_models);


for i=1+4*n_models:5*n_models+2%*n_splits
    
    

    if i==1+0*n_models
    folder=sprintf('/split00_0/');
    end
    if i==2+0*n_models
    folder=sprintf('/split00_1e-10/');
    end
    if i==3+0*n_models
    folder=sprintf('/split00_1e-8/');
    end
    if i==4+0*n_models
    folder=sprintf('/split00_1e-6/');
    end
    if i==5+0*n_models
    folder=sprintf('/split00_3e-6/');
    end
    if i==6+0*n_models
    folder=sprintf('/split00_6e-6/');
    end
    if i==7+0*n_models
    folder=sprintf('/split00_1e-5/');
    end
    if i==8+0*n_models
    folder=sprintf('/split00_3e-5/');
    end
    if i==9+0*n_models
    folder=sprintf('/split00_6e-5/');
    end
    if i==10+0*n_models
    folder=sprintf('/split00_1e-4/');
    end
    if i==11+0*n_models
    folder=sprintf('/split00_3e-4/');
    end
    if i==12+0*n_models
    folder=sprintf('/split00_6e-4/');
    end
    if i==13+0*n_models
    folder=sprintf('/split00_1e-3/');
    end
    if i==14+0*n_models
    folder=sprintf('/split00_3e-3/');
    end
    
    %{
    if i==1+1*n_models
    folder=sprintf('/split01_0/');
    end
    if i==2+1*n_models
    folder=sprintf('/split01_1e-10/');
    end
    if i==3+1*n_models
    folder=sprintf('/split01_1e-8/');
    end
    if i==4+1*n_models
    folder=sprintf('/split01_1e-6/');
    end
    if i==5+1*n_models
    folder=sprintf('/split01_3e-6/');
    end
    if i==6+1*n_models
    folder=sprintf('/split01_6e-6/');
    end
    if i==7+1*n_models
    folder=sprintf('/split01_1e-5/');
    end
    if i==8+1*n_models
    folder=sprintf('/split01_3e-5/');
    end
    if i==9+1*n_models
    folder=sprintf('/split01_6e-5/');
    end
    if i==10+1*n_models
    folder=sprintf('/split01_1e-4/');
    end
    if i==11+1*n_models
    folder=sprintf('/split01_3e-4/');
    end
    if i==12+1*n_models
    folder=sprintf('/split01_6e-4/');
    end
    if i==13+1*n_models
    folder=sprintf('/split01_1e-3/');
    end
    if i==14+1*n_models
    folder=sprintf('/split01_3e-3/');
    end
    
    
        if i==1+2*n_models
    folder=sprintf('/split03_0/');
    end
    if i==2+2*n_models
    folder=sprintf('/split03_1e-10/');
    end
    if i==3+2*n_models
    folder=sprintf('/split03_1e-8/');
    end
    if i==4+2*n_models
    folder=sprintf('/split03_1e-6/');
    end
    if i==5+2*n_models
    folder=sprintf('/split03_3e-6/');
    end
    if i==6+2*n_models
    folder=sprintf('/split03_6e-6/');
    end
    if i==7+2*n_models
    folder=sprintf('/split03_1e-5/');
    end
    if i==8+2*n_models
    folder=sprintf('/split03_3e-5/');
    end
    if i==9+2*n_models
    folder=sprintf('/split03_6e-5/');
    end
    if i==10+2*n_models
    folder=sprintf('/split03_1e-4/');
    end
    if i==11+2*n_models
    folder=sprintf('/split03_3e-4/');
    end
    if i==12+2*n_models
    folder=sprintf('/split03_6e-4/');
    end
    if i==13+2*n_models
    folder=sprintf('/split03_1e-3/');
    end
    if i==14+2*n_models
    folder=sprintf('/split03_3e-3/');
    end
    
    
        if i==1+3*n_models
    folder=sprintf('/split05_0/');
    end
    if i==2+3*n_models
    folder=sprintf('/split05_1e-10/');
    end
    if i==3+3*n_models
    folder=sprintf('/split05_1e-8/');
    end
    if i==4+3*n_models
    folder=sprintf('/split05_1e-6/');
    end
    if i==5+3*n_models
    folder=sprintf('/split05_3e-6/');
    end
    if i==6+3*n_models
    folder=sprintf('/split05_6e-6/');
    end
    if i==7+3*n_models
    folder=sprintf('/split05_1e-5/');
    end
    if i==8+3*n_models
    folder=sprintf('/split05_3e-5/');
    end
    if i==9+3*n_models
    folder=sprintf('/split05_6e-5/');
    end
    if i==10+3*n_models
    folder=sprintf('/split05_1e-4/');
    end
    if i==11+3*n_models
    folder=sprintf('/split05_3e-4/');
    end
    if i==12+3*n_models
    folder=sprintf('/split05_6e-4/');
    end
    if i==13+3*n_models
    folder=sprintf('/split05_1e-3/');
    end
    if i==14+3*n_models
    folder=sprintf('/split05_3e-3/');
    end
    
    
        if i==1+4*n_models
    folder=sprintf('/split07_0/');
    end
    if i==2+4*n_models
    folder=sprintf('/split07_1e-10/');
    end
    if i==3+4*n_models
    folder=sprintf('/split07_1e-8/');
    end
    if i==4+4*n_models
    folder=sprintf('/split07_1e-6/');
    end
    if i==5+4*n_models
    folder=sprintf('/split07_3e-6/');
    end
    if i==6+4*n_models
    folder=sprintf('/split07_6e-6/');
    end
    if i==7+4*n_models
    folder=sprintf('/split07_1e-5/');
    end
    if i==8+4*n_models
    folder=sprintf('/split07_3e-5/');
    end
    if i==9+4*n_models
    folder=sprintf('/split07_6e-5/');
    end
    if i==10+4*n_models
    folder=sprintf('/split07_1e-4/');
    end
    if i==11+4*n_models
    folder=sprintf('/split07_3e-4/');
    end
    if i==12+4*n_models
    folder=sprintf('/split07_6e-4/');
    end
    if i==13+4*n_models
    folder=sprintf('/split07_1e-3/');
    end
    if i==14+4*n_models
    folder=sprintf('/split07_3e-3/');
    end
    
    if i==1+5*n_models
    folder=sprintf('/split09_0/');
    end
    if i==2+5*n_models
    folder=sprintf('/split09_1e-10/');
    end
    if i==3+5*n_models
    folder=sprintf('/split09_1e-8/');
    end
    if i==4+5*n_models
    folder=sprintf('/split09_1e-6/');
    end
    if i==5+5*n_models
    folder=sprintf('/split09_3e-6/');
    end
    if i==6+5*n_models
    folder=sprintf('/split09_6e-6/');
    end
    if i==7+5*n_models
    folder=sprintf('/split09_1e-5/');
    end
    if i==8+5*n_models
    folder=sprintf('/split09_3e-5/');
    end
    if i==9+5*n_models
    folder=sprintf('/split09_6e-5/');
    end
    if i==10+5*n_models
    folder=sprintf('/split09_1e-4/');
    end
    if i==11+5*n_models
    folder=sprintf('/split09_3e-4/');
    end
    if i==12+5*n_models
    folder=sprintf('/split09_6e-4/');
    end
    if i==13+5*n_models
    folder=sprintf('/split09_1e-3/');
    end
    if i==14+5*n_models
    folder=sprintf('/split09_3e-3/');
    end
    

        if i==1+6*n_models
    folder=sprintf('/split10_0/');
    end
    if i==2+6*n_models
    folder=sprintf('/split10_1e-10/');
    end
    if i==3+6*n_models
    folder=sprintf('/split10_1e-8/');
    end
    if i==4+6*n_models
    folder=sprintf('/split10_1e-6/');
    end
    if i==5+6*n_models
    folder=sprintf('/split10_3e-6/');
    end
    if i==6+6*n_models
    folder=sprintf('/split10_6e-6/');
    end
    if i==7+6*n_models
    folder=sprintf('/split10_1e-5/');
    end
    if i==8+6*n_models
    folder=sprintf('/split10_3e-5/');
    end
    if i==9+6*n_models
    folder=sprintf('/split10_6e-5/');
    end
    if i==10+6*n_models
    folder=sprintf('/split10_1e-4/');
    end
    if i==11+6*n_models
    folder=sprintf('/split10_3e-4/');
    end
    if i==12+6*n_models
    folder=sprintf('/split10_6e-4/');
    end
    if i==13+6*n_models
    folder=sprintf('/split10_1e-3/');
    end
    if i==14+6*n_models
    folder=sprintf('/split10_3e-3/');
    end
    %}
    
    
    if i==1+1*n_models
    folder=sprintf('/split01_hi_0/');
    end
    if i==2+1*n_models
    folder=sprintf('/split01_hi_1e-10/');
    end
    if i==3+1*n_models
    folder=sprintf('/split01_hi_1e-8/');
    end
    if i==4+1*n_models
    folder=sprintf('/split01_hi_1e-6/');
    end
    if i==5+1*n_models
    folder=sprintf('/split01_hi_3e-6/');
    end
    if i==6+1*n_models
    folder=sprintf('/split01_hi_6e-6/');
    end
    if i==7+1*n_models
    folder=sprintf('/split01_hi_1e-5/');
    end
    if i==8+1*n_models
    folder=sprintf('/split01_hi_3e-5/');
    end
    if i==9+1*n_models
    folder=sprintf('/split01_hi_6e-5/');
    end
    if i==10+1*n_models
    folder=sprintf('/split01_hi_1e-4/');
    end
    if i==11+1*n_models
    folder=sprintf('/split01_hi_3e-4/');
    end
    if i==12+1*n_models
    folder=sprintf('/split01_hi_6e-4/');
    end
    if i==13+1*n_models
    folder=sprintf('/split01_hi_1e-3/');
    end
    if i==14+1*n_models
    folder=sprintf('/split01_hi_3e-3/');
    end
    
    
        if i==1+2*n_models
    folder=sprintf('/split03_hi_0/');
    end
    if i==2+2*n_models
    folder=sprintf('/split03_hi_1e-10/');
    end
    if i==3+2*n_models
    folder=sprintf('/split03_hi_1e-8/');
    end
    if i==4+2*n_models
    folder=sprintf('/split03_hi_1e-6/');
    end
    if i==5+2*n_models
    folder=sprintf('/split03_hi_3e-6/');
    end
    if i==6+2*n_models
    folder=sprintf('/split03_hi_6e-6/');
    end
    if i==7+2*n_models
    folder=sprintf('/split03_hi_1e-5/');
    end
    if i==8+2*n_models
    folder=sprintf('/split03_hi_3e-5/');
    end
    if i==9+2*n_models
    folder=sprintf('/split03_hi_6e-5/');
    end
    if i==10+2*n_models
    folder=sprintf('/split03_hi_1e-4/');
    end
    if i==11+2*n_models
    folder=sprintf('/split03_hi_3e-4/');
    end
    if i==12+2*n_models
    folder=sprintf('/split03_hi_6e-4/');
    end
    if i==13+2*n_models
    folder=sprintf('/split03_hi_1e-3/');
    end
    if i==14+2*n_models
    folder=sprintf('/split03_hi_3e-3/');
    end
    
    
        if i==1+3*n_models
    folder=sprintf('/split05_hi_0/');
    end
    if i==2+3*n_models
    folder=sprintf('/split05_hi_1e-10/');
    end
    if i==3+3*n_models
    folder=sprintf('/split05_hi_1e-8/');
    end
    if i==4+3*n_models
    folder=sprintf('/split05_hi_1e-6/');
    end
    if i==5+3*n_models
    folder=sprintf('/split05_hi_3e-6/');
    end
    if i==6+3*n_models
    folder=sprintf('/split05_hi_6e-6/');
    end
    if i==7+3*n_models
    folder=sprintf('/split05_hi_1e-5/');
    end
    if i==8+3*n_models
    folder=sprintf('/split05_hi_3e-5/');
    end
    if i==9+3*n_models
    folder=sprintf('/split05_hi_6e-5/');
    end
    if i==10+3*n_models
    folder=sprintf('/split05_hi_1e-4/');
    end
    if i==11+3*n_models
    folder=sprintf('/split05_hi_3e-4/');
    end
    if i==12+3*n_models
    folder=sprintf('/split05_hi_6e-4/');
    end
    if i==13+3*n_models
    folder=sprintf('/split05_hi_1e-3/');
    end
    if i==14+3*n_models
    folder=sprintf('/split05_hi_3e-3/');
    end
    
    
        if i==1+4*n_models
    folder=sprintf('/split07_hi_0/');
    end
    if i==2+4*n_models
    folder=sprintf('/split07_hi_1e-10/');
    end
    if i==3+4*n_models
    folder=sprintf('/split07_hi_1e-8/');
    end
    if i==4+4*n_models
    folder=sprintf('/split07_hi_1e-6/');
    end
    if i==5+4*n_models
    folder=sprintf('/split07_hi_3e-6/');
    end
    if i==6+4*n_models
    folder=sprintf('/split07_hi_6e-6/');
    end
    if i==7+4*n_models
    folder=sprintf('/split07_hi_1e-5/');
    end
    if i==8+4*n_models
    folder=sprintf('/split07_hi_3e-5/');
    end
    if i==9+4*n_models
    folder=sprintf('/split07_hi_6e-5/');
    end
    if i==10+4*n_models
    folder=sprintf('/split07_hi_1e-4/');
    end
    if i==11+4*n_models
    folder=sprintf('/split07_hi_3e-4/');
    end
    if i==12+4*n_models
    folder=sprintf('/split07_hi_6e-4/');
    end
    if i==13+4*n_models
    folder=sprintf('/split07_hi_1e-3/');
    end
    if i==14+4*n_models
    folder=sprintf('/split07_hi_3e-3/');
    end
    
    if i==1+5*n_models
    folder=sprintf('/split09_hi_0/');
    end
    if i==2+5*n_models
    folder=sprintf('/split09_hi_1e-10/');
    end
    if i==3+5*n_models
    folder=sprintf('/split09_hi_1e-8/');
    end
    if i==4+5*n_models
    folder=sprintf('/split09_hi_1e-6/');
    end
    if i==5+5*n_models
    folder=sprintf('/split09_hi_3e-6/');
    end
    if i==6+5*n_models
    folder=sprintf('/split09_hi_6e-6/');
    end
    if i==7+5*n_models
    folder=sprintf('/split09_hi_1e-5/');
    end
    if i==8+5*n_models
    folder=sprintf('/split09_hi_3e-5/');
    end
    if i==9+5*n_models
    folder=sprintf('/split09_hi_6e-5/');
    end
    if i==10+5*n_models
    folder=sprintf('/split09_hi_1e-4/');
    end
    if i==11+5*n_models
    folder=sprintf('/split09_hi_3e-4/');
    end
    if i==12+5*n_models
    folder=sprintf('/split09_hi_6e-4/');
    end
    if i==13+5*n_models
    folder=sprintf('/split09_hi_1e-3/');
    end
    if i==14+5*n_models
    folder=sprintf('/split09_hi_3e-3/');
    end
    

        if i==1+6*n_models
    folder=sprintf('/split10_hi_0/');
    end
    if i==2+6*n_models
    folder=sprintf('/split10_hi_1e-10/');
    end
    if i==3+6*n_models
    folder=sprintf('/split10_hi_1e-8/');
    end
    if i==4+6*n_models
    folder=sprintf('/split10_hi_1e-6/');
    end
    if i==5+6*n_models
    folder=sprintf('/split10_hi_3e-6/');
    end
    if i==6+6*n_models
    folder=sprintf('/split10_hi_6e-6/');
    end
    if i==7+6*n_models
    folder=sprintf('/split10_hi_1e-5/');
    end
    if i==8+6*n_models
    folder=sprintf('/split10_hi_3e-5/');
    end
    if i==9+6*n_models
    folder=sprintf('/split10_hi_6e-5/');
    end
    if i==10+6*n_models
    folder=sprintf('/split10_hi_1e-4/');
    end
    if i==11+6*n_models
    folder=sprintf('/split10_hi_3e-4/');
    end
    if i==12+6*n_models
    folder=sprintf('/split10_hi_6e-4/');
    end
    if i==13+6*n_models
    folder=sprintf('/split10_hi_1e-3/');
    end
    if i==14+6*n_models
    folder=sprintf('/split10_hi_3e-3/');
    end
    
    i
    
c= ['./output' folder 'weathout'];
fip = fopen([c]);

n_step=fread(fip,1,'double');
weath_out_modulo=fread(fip,1,'double');

%pause(0.002)
%fclose(fip);
%end
%pause(20000)
%for i=1:2


%n_step=485000

step=zeros(1,n_step/weath_out_modulo);
mean_weath=zeros(n_step/weath_out_modulo,1);
mean_erosion=zeros(n_step/weath_out_modulo,1);
mean_diff=zeros(n_step/weath_out_modulo,1);
mean_moved_fluvial_sediment=zeros(n_step/weath_out_modulo,1);
mean_topsedi=zeros(n_step/weath_out_modulo,1);
mean_sedimentthickness=zeros(n_step/weath_out_modulo,1);
river_nodes=zeros(n_step/weath_out_modulo,1);
mean_bed=zeros(n_step/weath_out_modulo,1);

%n_step=42000
tic
for j=1:n_step/weath_out_modulo
    step(j)=fread(fip,1,'double');
    mean_weath(j,1)=fread(fip,1,'double');
    mean_erosion(j,1)=fread(fip,1,'double');
    mean_diff(j,1)=fread(fip,1,'double');
    mean_moved_fluvial_sediment(j,1)=fread(fip,1,'double');
    mean_topsedi(j,1)=fread(fip,1,'double');
    mean_sedimentthickness(j,1)=fread(fip,1,'double');
    river_nodes(j,1)=fread(fip,1,'double');
    mean_bed(j,1)=fread(fip,1,'double');
end
toc

if i<n_models+1
    mean_weath_list0(i)=mean(mean_weath(end-1000:end));
    mean_erosion_list0(i)=mean(mean_erosion(end-1000:end));
    %save('0.mat','mean_weath_list0','mean_erosion_list0');
end

if i>n_models & i<n_models*2+1
   mean_weath_list01(i-n_models*1)=mean(mean_weath(end-1000:end));
   mean_erosion_list01(i-n_models*1)=mean(mean_erosion(end-1000:end));
   %save('01.mat','mean_weath_list01','mean_erosion_list01');

end 


if i>n_models*2 & i<n_models*3+1
   mean_weath_list03(i-n_models*2)=mean(mean_weath(end-1000:end));
   mean_erosion_list03(i-n_models*2)=mean(mean_erosion(end-1000:end));
   %save('03.mat','mean_weath_list03','mean_erosion_list03');
end 


if i>n_models*3 & i<n_models*4+1
   mean_weath_list05(i-n_models*3)=mean(mean_weath(end-1000:end));
   mean_erosion_list05(i-n_models*3)=mean(mean_erosion(end-1000:end));
   %save('05.mat','mean_weath_list05','mean_erosion_list05');
end 


if i>n_models*4 & i<n_models*5+1
   mean_weath_list07(i-n_models*4)=mean(mean_weath(end-1000:end));
   mean_erosion_list07(i-n_models*4)=mean(mean_erosion(end-1000:end));
   %save('07.mat','mean_weath_list07','mean_erosion_list07');
end 

if i>n_models*5 & i<n_models*6+1
   mean_weath_list09(i-n_models*5)=mean(mean_weath(end-1000:end));
   mean_erosion_list09(i-n_models*5)=mean(mean_erosion(end-1000:end));
   %save('09.mat','mean_weath_list09','mean_erosion_list09');

end 

if i>n_models*6 & i<n_models*7+1
   mean_weath_list10(i-n_models*6)=mean(mean_weath(end-1000:end));
   mean_erosion_list10(i-n_models*6)=mean(mean_erosion(end-1000:end));
   %save('10.mat','mean_weath_list10','mean_erosion_list10');
end 

tic
figure(1)
plot(step,mean_erosion)
title('Mean Erosion')
hold all
legend('0','1e-10','1e-8','1e-7','1e-6','3e-6','1e-5','3e-5','1e-4','2e-4','4e-4','8e-4','1e-3','1.5e-3','2e-3','3e-3','4e-3','6e-3','8e-3','1e-2','1.5e-2','2e-2','2.5e-2','3e-2','4e-2','6e-2','8e-2','1e-1','2e-1','4e-1','1e-0')

figure(2)
plot(step,mean_weath)
title('Mean weath')
hold all
legend('0','1e-10','1e-8','1e-7','1e-6','3e-6','1e-5','3e-5','1e-4','2e-4','4e-4','8e-4','1e-3','1.5e-3','2e-3','3e-3','4e-3','6e-3','8e-3','1e-2','1.5e-2','2e-2','2.5e-2','3e-2','4e-2','6e-2','8e-2','1e-1','2e-1','4e-1','1e-0')

figure(3)
plot(step,mean_diff)
title('Mean diff')
hold all
legend('0','1e-10','1e-8','1e-7','1e-6','3e-6','1e-5','3e-5','1e-4','2e-4','4e-4','8e-4','1e-3','1.5e-3','2e-3','3e-3','4e-3','6e-3','8e-3','1e-2','1.5e-2','2e-2','2.5e-2','3e-2','4e-2','6e-2','8e-2','1e-1','2e-1','4e-1','1e-0')

figure(4)
plot(step,mean_moved_fluvial_sediment)
title('mean moved fluvial sediment')
hold all
legend('0','1e-10','1e-8','1e-7','1e-6','3e-6','1e-5','3e-5','1e-4','2e-4','4e-4','8e-4','1e-3','1.5e-3','2e-3','3e-3','4e-3','6e-3','8e-3','1e-2','1.5e-2','2e-2','2.5e-2','3e-2','4e-2','6e-2','8e-2','1e-1','2e-1','4e-1','1e-0')

figure(5)
plot(step,mean_topsedi)
title('mean topsedi')
hold all
legend('0','1e-10','1e-8','1e-7','1e-6','3e-6','1e-5','3e-5','1e-4','2e-4','4e-4','8e-4','1e-3','1.5e-3','2e-3','3e-3','4e-3','6e-3','8e-3','1e-2','1.5e-2','2e-2','2.5e-2','3e-2','4e-2','6e-2','8e-2','1e-1','2e-1','4e-1','1e-0')

figure(6)
plot(step,mean_sedimentthickness)
title('mean sediment thickness')
hold all
legend('0','1e-10','1e-8','1e-7','1e-6','3e-6','1e-5','3e-5','1e-4','2e-4','4e-4','8e-4','1e-3','1.5e-3','2e-3','3e-3','4e-3','6e-3','8e-3','1e-2','1.5e-2','2e-2','2.5e-2','3e-2','4e-2','6e-2','8e-2','1e-1','2e-1','4e-1','1e-0')

figure(7)
plot(cumsum(mean_erosion))
title('summed erosion')
hold all
legend('0','1e-10','1e-8','1e-7','1e-6','3e-6','1e-5','3e-5','1e-4','2e-4','4e-4','8e-4','1e-3','1.5e-3','2e-3','3e-3','4e-3','6e-3','8e-3','1e-2','1.5e-2','2e-2','2.5e-2','3e-2','4e-2','6e-2','8e-2','1e-1','2e-1','4e-1','1e-0')


figure(8)
plot(mean_weath(end),mean_erosion(end),'*')
title('Erosion v weath')
ylabel('Last erosion')
xlabel('Last weath')
hold all
legend('0','1e-10','1e-8','1e-7','1e-6','3e-6','1e-5','3e-5','1e-4','2e-4','4e-4','8e-4','1e-3','1.5e-3','2e-3','3e-3','4e-3','6e-3','8e-3','1e-2','1.5e-2','2e-2','2.5e-2','3e-2','4e-2','6e-2','8e-2','1e-1','2e-1','4e-1','1e-0')
ylim([0 5e-3])
xlim([0 5e-3])


figure(9)
plot(cumsum(mean_weath))
title('summed weath')
hold all


figure(10)
plot(cumsum(mean_erosion)+cumsum(mean_weath))
title('summed weath and summed erosion')
hold all

figure(11)
plot(mean_bed(1)+1500*2e-3-cumsum(mean_erosion.*river_nodes/(150*150))-cumsum(mean_weath)-mean_bed(end))
title('summed weath and summed erosion')
hold all
legend('0','1e-10','1e-8','1e-7','1e-6','3e-6','1e-5','3e-5','1e-4','2e-4','4e-4','8e-4','1e-3','1.5e-3','2e-3','3e-3','4e-3','6e-3','8e-3','1e-2','1.5e-2','2e-2','2.5e-2','3e-2','4e-2','6e-2','8e-2','1e-1','2e-1','4e-1','1e-0')


figure(12)
plot(step,river_nodes)
title('Amount of river nodes')
hold all
legend('0','1e-10','1e-8','1e-7','1e-6','3e-6','1e-5','3e-5','1e-4','2e-4','4e-4','8e-4','1e-3','1.5e-3','2e-3','3e-3','4e-3','6e-3','8e-3','1e-2','1.5e-2','2e-2','2.5e-2','3e-2','4e-2','6e-2','8e-2','1e-1','2e-1','4e-1','1e-0')


figure(13)
plot(mean(mean_diff),mean(mean_erosion),'*')
title('Erosion v diff')
ylabel('Mean erosion')
xlabel('Mean diff')
hold all
legend('0','1e-10','1e-8','1e-7','1e-6','3e-6','1e-5','3e-5','1e-4','2e-4','4e-4','8e-4','1e-3','1.5e-3','2e-3','3e-3','4e-3','6e-3','8e-3','1e-2','1.5e-2','2e-2','2.5e-2','3e-2','4e-2','6e-2','8e-2','1e-1','2e-1','4e-1','1e-0')
ylim([0 5e-3])
xlim([0 5e-3])
toc

fclose(fip);

end

tilefigs