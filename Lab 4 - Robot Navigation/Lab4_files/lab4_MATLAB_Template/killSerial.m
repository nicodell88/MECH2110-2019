function killSerial()
%killSerial kills all open serial ports

serialObj = instrfind;
delete(serialObj);
end

