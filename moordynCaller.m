function lineForces = moordynCaller(disp,vel,time,dt)
    % function calls MoorDyn library to calculate and return the mooring
    % line forces at every time step.
    mdStruct = evalin('base','mdStruct');
    lineForces = zeros(1,length(disp));
    lineForcesPtr = libpointer('doublePtr',lineForces);
    calllib('libmoordyn', 'MoorDyn_Step', mdStruct, disp, vel, lineForcesPtr, time, dt);
    lineForces = lineForcesPtr.value;
    clear lineForcesPtr
end 