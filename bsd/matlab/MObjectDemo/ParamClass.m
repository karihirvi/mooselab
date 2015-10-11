classdef ParamClass < handle & matlab.mixin.Copyable
%PARAMCLASS Demo parameter class for signals
%   Part of MObjectDemo project

properties
  value 
end

methods
  function self = ParamClass(value)
    self.value = value;
  end
  
  
end
  
end

