local sName

function OnStart(a_host, a_eEntity, a_initTable)
    sName = a_initTable.sEntityName
end

function OnUpdate(a_host, a_eEntity, a_nDt)

	results = _OnTrigger(a_eEntity)
	for i = 0, #results do
		if results[i].hasHit then
			if results[i].name == sName then
				_DestroyEnt(results[i].entity)
			end		
		end
	end

end