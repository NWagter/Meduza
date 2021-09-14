local yRotSpeed = 50

function OnUpdate(a_host, a_entity, a_dt)

    _Rotate(a_entity, 0, yRotSpeed * a_dt, 0)
end