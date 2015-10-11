classdef Server < MObject
%SERVER Demo class for emitting signals
%   Part of MObjectDemo project

properties
end

methods
  function self = Server()
  end
  
  function emitWithNoParameters(self)
    self.emit('no params');
  end
  
  function emitWithParameters(self)    
    self.emit('with params', 123);
    self.emit('with params', ParamClass('some value'));
  end
end

end

