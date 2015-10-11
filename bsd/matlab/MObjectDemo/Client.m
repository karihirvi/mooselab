classdef Client
%CLIENT Demo class for receiving signals
%   Part of MObjectDemo project

properties
  name
end

methods
  function self = Client(name)
    self.name = name;
  end
  
  function slotNoParams(self)
    fprintf('slotNoParams called on object %s\n', self.name);
  end
  
  function slotWithParams(self, param)
    fprintf('slotWithParams called on object %s\n', self.name);
    display(param);
  end
  
end
  
end

