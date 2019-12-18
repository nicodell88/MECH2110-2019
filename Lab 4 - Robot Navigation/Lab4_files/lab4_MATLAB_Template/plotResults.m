function plotResults(Tplots,Zplots,PWMplots,Yplots)
%% Time-series plots
figure(2)
clf
subplot(5,1,1)
plot(Tplots,Zplots(:,1));
title('World fixed positions');
xlabel('Time [s]');
ylabel('North [m]');
subplot(5,1,2)
plot(Tplots,Zplots(:,4));
title('Body fixed velocities');
xlabel('Time [s]');
ylabel('Surge [m/s]');
subplot(5,1,3)
plot(Tplots,Zplots(:,2));
xlabel('Time [s]');
ylabel('East [m]');
subplot(5,1,4)
plot(Tplots,Zplots(:,5));
xlabel('Time [s]');
ylabel('Sway [m/s]');
subplot(5,1,5)
plot(Tplots,Zplots(:,3));
xlabel('Time [s]');
ylabel('Yaw [rad]');
%% PWM plots
figure(3)
clf
subplot(2,1,1)
plot(Tplots,PWMplots(:,1));
title('Left PWM');
xlabel('Time [s]');
ylabel('PWM');
ylim([-255 255])
subplot(2,1,2)
plot(Tplots,PWMplots(:,2));
title('Right PWM');
xlabel('Time [s]');
ylabel('PWM');
ylim([-255 255])
%% Sensor Plots
figure(4)
subplot(3,1,1)
plot(Tplots,Yplots(:,1));
xlabel('Time [s]')
ylabel('Left Sensor [mm]')

subplot(3,1,2)
plot(Tplots,Yplots(:,2));
xlabel('Time [s]')
ylabel('Right Sensor [mm]')

subplot(3,1,3)
plot(Tplots,Yplots(:,3));
xlabel('Time [s]')
ylabel('Front Sensor [mm]')
end