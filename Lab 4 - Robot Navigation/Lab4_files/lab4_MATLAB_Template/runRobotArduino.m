killSerial;
%% clean up
clear all
clc
%% Set up serial
%TODO: change to your Arduino's COM port!
% sobj = 'COM3'; %Windows Example
sobj = '/dev/cu.wchusbserial142240';%MAC/Linux Example

s = serial(sobj,'BaudRate',115200,'timeout',1);
fopen(s);
pause(2);
%% Animation
video = 0; %if this variable is set to 1 a video of the simulation will be written to to '<filename>.mp4'
filename = 'myfile';
if video
    v=VideoWriter(filename, 'MPEG-4');
    open(v);
end
%% draw the track
figure(1); clf; hold on
[obstacle,zone] = GenerateTrack();
grid minor;
%% initialise robot
robot = generateRobot();
%% Initialise sensor locations
sensor = generateSensors();
drawnow
%% Initial Conditions
eta=[1200;1200-290;-pi/2];  %XY-psi not NE-psi

dT=0.05;    %50ms => 20Hz
Tsim=50;    %simulation time

Z=[1e-3*eta(2),1e-3*eta(1),-eta(3),0,0]';%robot starting position
pwm=[0;0];%initial motor pwm

%% Waitbar
delete(findall(0,'tag','TMWWaitbar')); %Delete any stuck waitbars
H = waitbar(0,'Navigation Assignment', ...
    'Name', 'MECH2110', ...
    'CreateCancelBtn', 'setappdata(gcbf,''canceling'',1)'); % Create new waitbar
%% Variables for plotting
N = Tsim/dT;
Tplots   = nan(N,1);
Zplots   = nan(N,5);
PWMplots = nan(N,2);
Yplots   = nan(N,3);
%% Run Simulation
iter = 0;
for t=0:dT:Tsim
    iter = iter+1;
    if getappdata(H,'canceling') %Check to see if cancel button was hit
        break
    end
    if findCrash(eta,robot,obstacle)
        robot(1).patch.XData=robot(1).patch.XData+50*randn(length(robot(1).patch.XData),1); robot(1).patch.YData=robot(1).patch.YData+50*randn(length(robot(1).patch.YData),1);
        fprintf('Your robot has crashed!\n');
        break
    end
    
    try %harder
        waitbar(t/Tsim,H)
        %% Simulate Plant
%% Simulate Vehicle
        odefun=@(time,states)vehicleModel2020(time,states,pwm);%simulate vehicle
        [Tout,Z] = ode23(odefun,[t t+dT],Z);
        Z=Z(end,:)';
        eta = [1e3*Z(2);1e3*Z(1);-Z(3)];
             %% Simulate Measurements
               [y,sensor] = sensorMeasurements(eta,sensor,obstacle);
        %% Update Figure
        zone = updateZone(zone,eta);
        robot = drawRobot(robot,eta);
        drawnow; 
        %% make decisions
        
        fprintf(s,'sensorL %0.2f\n\r',y(1));
        fprintf(s,'sensorR %0.2f\n\r',y(2));
        fprintf(s,'sensorF %0.2f\n\r',y(3));
        pwm = query(s,'ctrl?','%s\r','%d,%d\n\r');
        
        
        %% video
        if video
            frame = getframe(gcf);
            writeVideo(v,frame);
        end
        %% save data
        Tplots(iter,:)   =  Tout(end,end);
        Zplots(iter,:)   =  Z.';
        PWMplots(iter,:) =  pwm.';
        Yplots(iter,:)   =  y.';
    catch football
        delete(H);
        fclose(s); delete(s); clear s   % Close serial connection and clean up
        if video
            close(v)
        end
        rethrow(football);
    end
end
delete(H);
fclose(s); delete(s); clear s   % Close serial connection and clean up
if video
    frame = getframe(1);
    writeVideo(v,frame);
    close(v);
end
%% Mark Simulation
gradeSim(Tplots,robot,Zplots,zone);
%% Plot Results
plotResults(Tplots,Zplots,PWMplots,Yplots);