local sName
local cBaseColour
local cOverlapColour

function OnStart(a_host, a_eEntity, a_initTable)
    sName = a_initTable.sEntityName

    cBaseColour = _GetColour(a_eEntity)
    cOverlapColour = _CreateColour(1,0,1,1)
end

function OnUpdate(a_host, a_eEntity, a_nDt)

	local bTriggered = false
	
	results = _OnTrigger(a_eEntity)
	for i = 1, #results do
		if results[i].hasHit then
			if results[i].name == sName then
				bTriggered = true
			end		
		end	
	end
	
	if bTriggered then
		_SetColour(a_eEntity, cOverlapColour)
	
	else	
		_SetColour(a_eEntity, cBaseColour)
	end
end