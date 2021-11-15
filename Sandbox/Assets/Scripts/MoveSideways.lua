local bLeft = true
local fTime = 1

function OnUpdate(a_host, a_entity, a_fDT)

    fTime = fTime - a_fDT
    vMovement = _CreateVector3()
    xSpeed = 5

    if bLeft == true then
        xSpeed = -5
    else
        xSpeed = 5
    end

    if fTime < 0 then
        if bLeft == true then
            bLeft = false
        else
            bLeft = true
        end

        fTime = 2
    end

    vMovement.x = xSpeed * a_fDT
    _Move(a_entity, vMovement)
end