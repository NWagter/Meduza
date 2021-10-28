local vScale;
local bShouldScaleUp = false

function OnStart(a_host, a_entity)
  vScale = _CreateVector3()
  vScale.x = 1;
  vScale.y = 1;
  vScale.z = 1;
end

function OnUpdate(a_host, a_entity, a_fDT)
       
  if bShouldScaleUp then
      vScale.x = vScale.x + a_fDT
      vScale.y = vScale.y + a_fDT
      vScale.z = vScale.z + a_fDT
  else
      vScale.x = vScale.x - a_fDT
      vScale.y = vScale.y - a_fDT
      vScale.z = vScale.z - a_fDT
  end

    if vScale.x > 4 then
      bShouldScaleUp = false
    elseif vScale.x < 1 then
      bShouldScaleUp = true
    end


    _SetScale(a_entity, vScale)

  end