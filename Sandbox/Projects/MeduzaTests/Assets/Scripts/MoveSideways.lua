local bLeft = true
local nTime = 1

function OnUpdate(a_host, a_eEntity, a_nDt)

    nTime = nTime - a_nDt
    vMovement = _CreateVector3()
    nXSpeed = 5

    if bLeft == true then
        nXSpeed = -5
    else
        nXSpeed = 5
    end

    if nTime < 0 then
        if bLeft == true then
            bLeft = false
        else
            bLeft = true
        end

        nTime = 2
    end

    vMovement.x = nXSpeed * a_nDt
    _Move(a_eEntity, vMovement)
end