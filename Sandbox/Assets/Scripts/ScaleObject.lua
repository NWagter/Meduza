local vScale;
local bShouldScaleUp = false

function OnStart(a_host, a_eEntity)
  print("Created Vec 1,1,1")
  vScale = _CreateVector3(1,1,1)
end

function OnUpdate(a_host, a_eEntity, a_nDt)
       
  if bShouldScaleUp then
      vScale.x = vScale.x + a_nDt
      vScale.y = vScale.y + a_nDt
      vScale.z = vScale.z + a_nDt
  else
      vScale.x = vScale.x - a_nDt
      vScale.y = vScale.y - a_nDt
      vScale.z = vScale.z - a_nDt
  end

    if vScale.x > 4 then
      bShouldScaleUp = false
    elseif vScale.x < 1 then
      bShouldScaleUp = true
    end


    _SetScale(a_eEntity, vScale)

  end