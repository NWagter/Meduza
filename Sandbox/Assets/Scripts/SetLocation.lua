local scale = 1
local shouldScaleUp = 0

function OnUpdate(a_host, a_entity, a_dt)
    _SetLocation(a_entity, 0, 0, 10)
    _SetRotation(a_entity, 0, 180, 0)      

    if shouldScaleUp == 1 then
      scale = scale + a_dt
    elseif shouldScaleUp == 0 then
      scale = scale - a_dt
    end

    if scale > 4 then
      shouldScaleUp = 0
    elseif scale < 1 then
      shouldScaleUp = 1
    end


    _SetScale(a_entity, scale,scale,scale)

  end