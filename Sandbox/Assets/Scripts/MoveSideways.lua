local left = true
local time = 1

function OnUpdate(a_host, a_entity, a_dt)

    time = time - a_dt

    xSpeed = 5

    if left == true then
        xSpeed = -5
    else
        xSpeed = 5
    end

    if time < 0 then
        if left == true then
            left = false
            _FlipX(a_entity)
        else
            left = true
            _FlipX(a_entity)
        end

        time = 2
    end


    _Translate(a_entity, xSpeed * a_dt, 0, 0)
end