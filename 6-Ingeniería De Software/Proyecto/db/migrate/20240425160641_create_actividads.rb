class CreateActividads < ActiveRecord::Migration[7.0]
  def change
    create_table :actividads do |t|
      t.string :titulo
      t.integer :cantidad_personas
      t.integer :precio
      t.date :fecha
      t.references :user, null: false, foreign_key: true

      t.timestamps
    end
  end
end
