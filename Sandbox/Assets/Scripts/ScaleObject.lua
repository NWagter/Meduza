local fScale = 1
local bShouldScaleUp = 0

function OnUpdate(a_host, a_entity, a_fDT)
    _SetLocation(a_entity, 0, 0, 10)
    _SetRotation(a_entity, 0, 180, 0)      

    if bShouldScaleUp == 1 then
      scale = fScale + a_fDT
    elseif bShouldScaleUp == 0 then
      scale = fScale - a_fDT
    end

    if fScale > 4 then
      bShouldScaleUp = 0
    elseif fScale < 1 then
      bShouldScaleUp = 1
    end


    _SetScale(a_entity, fScale, fScale, fScale)

  end