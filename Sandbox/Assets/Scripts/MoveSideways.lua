local bLeft = true
local fTime = 1

function OnUpdate(a_host, a_entity, a_fDT)

    fTime = fTime - a_fDT

    xSpeed = 5

    if bLeft == true then
        xSpeed = -5
    else
        xSpeed = 5
    end

    if fTime < 0 then
        if bLeft == true then
            bLeft = false
            _FlipX(a_entity)
        else
            bLeft = true
            _FlipX(a_entity)
        end

        fTime = 2
    end


    _Translate(a_entity, xSpeed * a_fDT, 0, 0)
end