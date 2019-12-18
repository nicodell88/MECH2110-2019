function [pwm] = ctrlAlloc(y)
%ctrlAlloc Takes measurements from the robot's sensors and determines what
%control action to make.
yLeft  = y(1);
yRight = y(2);
yFront = y(3);

%The following is an example of how you might want to set up a state
%machine in matlab using persistent variables for the state, this value
%remains the same between calls to this function but is reset by the clear
%all at the beginning of the simulation.

%define states
FORWARD = 0;
REVERSE = 1;

persistent state
if isempty(state)
    state = FORWARD;
end

switch state
    case FORWARD
        pwmL = 130;
        pwmR = 100;
        %Transition condition
        if(yFront<200)
            state = REVERSE;
        end
    %break; would go here in C
    case REVERSE
        pwmL = -55;
        pwmR = -50;
        %Transition condition
        
    %break; would go here in C
    otherwise%this becomes default in C instead of otherwise
end


pwm = [pwmL;pwmR];
end