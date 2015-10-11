classdef MObject < handle
%MOBJECT Signal and slot implemetation similar to Qt's
%   See http://doc.qt.io/qt-5/signalsandslots.html
%   In Matlab implementation, no need to explicitly define signals and
%   slots.
%   If an object wants to emit a signal, it needs to be derived from 
%   MObject. To just receice signals (i.e. to contain slots) the
%   derivation is not necessary.
%

properties (GetAccess = public, SetAccess = private)
  signalToSlots
end

methods (Static)
  function ret = GetSetDebug(varargin)
  % Implements class wide debug options store
    persistent debug
    ret = [];
    if isempty(debug)
      debug = [MObjectDebug.warnMultipleConnections];
    end
    if isempty(varargin)
      ret = debug;
    else
      assert(isa(varargin{1}, 'MObjectDebug'));
      debug = varargin{1};
    end
  end
end

methods
  function self = MObject()
    self.signalToSlots = containers.Map();
  end

  function connect(self, signal, toFuncH)
  % Connects a signal (=string) to function handle (=slot). The signal
  % can be received by multiple slots.
    if isKey(self.signalToSlots, signal)
      tmp = self.signalToSlots(signal);
      % warn/error if a connection exists already
      for i = 1:length(tmp)
        if strcmp(func2str(toFuncH), func2str(tmp{i}))
          d = MObject.GetSetDebug();
          str = sprintf(['Connecting signal ''%s'' to slot ''%s''' ...
            'multiple times'], signal, func2str(toFuncH));
          if ismember(MObjectDebug.errorMultipleConnections, d)
            error(str); %#ok<SPERR>
          elseif ismember(MObjectDebug.warnMultipleConnections, d)
            warning(str); %#ok<SPWRN>
          end
        end
      end
      tmp = self.signalToSlots(signal);
      self.signalToSlots(signal) = [tmp {toFuncH}];
    else      
      self.signalToSlots(signal) = {toFuncH};
    end

  end

  function emit(self, signal, varargin)
  % Emit a signal
    if isKey(self.signalToSlots, signal)
      slots = self.signalToSlots(signal);
      N = length(varargin);
      % loop over slots and call them
      for i=1:length(slots)
        toFuncH = slots{i};      
        copyArgs = cell(N,1);
        for j=1:N
          obj = varargin{j};
          % If a signal/slot argument is a handle class, we need to copy
          % it to prevent unintented argument modifications by the slot
          % function.
          if isa(obj, 'handle')
            copyArgs{j} = copy(obj);
          else
            copyArgs{j} = obj;
          end
        end
        % call the object method
        toFuncH(copyArgs{:});
      end    
    else
      d = MObject.GetSetDebug();
      str = sprintf(['Signal ''%s'' emitted, but there were no' ...
        'receiving slots.'], signal);
      if ismember(MObjectDebug.errorNoReceivers, d)
        error(str); %#ok<SPERR>
      elseif ismember(MObjectDebug.warnNoReceivers, d)
        warning(str); %#ok<SPWRN>
      end        
    end
  end  
end

end